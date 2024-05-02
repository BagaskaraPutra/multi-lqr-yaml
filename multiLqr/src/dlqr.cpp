#include "dlqr.hpp"

namespace multilqr
{
Dlqr::Dlqr(const std::string& configPath)
{
    _pContinuousSystem = NULL;
    _pDiscreteSystem = NULL;
    if (!loadConfigConstructor(configPath)){
        return;
    }
    if (!calcGain()){
        return;
    }
}

Dlqr::Dlqr(const Eigen::MatrixXd& A, 
        const Eigen::MatrixXd& B,
        const Eigen::MatrixXd& Q,
        const Eigen::MatrixXd& R)
{
    _pDiscreteSystem = new DiscreteLtiStateSpace(A,B);
    _pContinuousSystem = (ContinuousLtiStateSpace*) _pDiscreteSystem;
    _Q = Q;
    _R = R;
    calcGain();
}

Dlqr::Dlqr(YAML::Node &lqrNode)
{
    _pContinuousSystem = NULL;
    _pDiscreteSystem = NULL;
    if (!LoadConfigLqrNode(lqrNode)){
        return;
    };
    calcGain();
}

Dlqr::~Dlqr()
{
    delete _pContinuousSystem;
    delete _pDiscreteSystem;
}

bool Dlqr::LoadConfigLqrNode(YAML::Node& lqrNode)
{ 
    YAML::Node ssNode = lqrNode["stateSpace"];
    _num_inputs = ssNode["num_inputs"].as<int>();
    _num_states = ssNode["num_states"].as<int>();
    _num_outputs = ssNode["num_outputs"].as<int>();

    YAML::Node contNode = ssNode["continuous"];
    YAML::Node discNode = ssNode["discrete"];

    // Prioritize loading discrete-time systems before continuous-time
    bool discrete = false;
    if (discNode){
        Eigen::MatrixXd A = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(discNode["A"].as<std::vector<double>>().data(), _num_states, _num_states);
        Eigen::MatrixXd B = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(discNode["B"].as<std::vector<double>>().data(), _num_states, _num_inputs);
        Eigen::MatrixXd C = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(discNode["C"].as<std::vector<double>>().data(), _num_outputs, _num_states);
        Eigen::MatrixXd D = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(discNode["D"].as<std::vector<double>>().data(), _num_outputs, _num_inputs);
        double samplingPeriod = discNode["samplingPeriod"].as<double>();

        if (_pDiscreteSystem == NULL){
            _pDiscreteSystem = new DiscreteLtiStateSpace (A, B, C, D, samplingPeriod);
            _pDiscreteSystem->PrintParameters();
        } else {
            _pDiscreteSystem->SetABCD(A,B,C,D,samplingPeriod);
        }
        if (_pContinuousSystem == NULL){
            _pContinuousSystem = new ContinuousLtiStateSpace();
        }
        StateSpaceUtils::d2c(_pDiscreteSystem, _pContinuousSystem);
        discrete = true;
    };  

    if (contNode != NULL && !discrete){
        Eigen::MatrixXd A = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(contNode["A"].as<std::vector<double>>().data(), _num_states, _num_states);
        Eigen::MatrixXd B = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(contNode["B"].as<std::vector<double>>().data(), _num_states, _num_inputs);
        Eigen::MatrixXd C = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(contNode["C"].as<std::vector<double>>().data(), _num_outputs, _num_states);
        Eigen::MatrixXd D = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(contNode["D"].as<std::vector<double>>().data(), _num_outputs, _num_inputs);
        
        if (_pContinuousSystem == NULL){
            _pContinuousSystem = new ContinuousLtiStateSpace (A, B, C, D);
            _pContinuousSystem->PrintParameters();
        } else {
            _pContinuousSystem->SetABCD(A,B,C,D);
        }
        
        if (_pDiscreteSystem == NULL){
            _pDiscreteSystem = new DiscreteLtiStateSpace();
        }
        
        double samplingPeriod = contNode["samplingPeriod"].as<double>();
        if (samplingPeriod) {
            StateSpaceUtils::c2d(_pContinuousSystem, _pDiscreteSystem, samplingPeriod);
            _pDiscreteSystem->PrintParameters();
        }
    }

    YAML::Node weightsNode = lqrNode["weights"];
    _Q = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(weightsNode["Q"].as<std::vector<double>>().data(), _num_states, _num_states);
    _R = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::RowMajor>(weightsNode["R"].as<std::vector<double>>().data(), _num_inputs, _num_inputs);
    
    return true;
}

bool Dlqr::loadConfigConstructor(const std::string& configPath)
{ 
    YAML::Node lqrNode;
    try
    {
        lqrNode = YAML::LoadFile(configPath.c_str());
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to load: " << configPath << std::endl;
        return false;
    }

    LoadConfigLqrNode(lqrNode);
    std::cout<<"[Dlqr] Finished loading config constructor: "<<configPath<<std::endl;
    return true;
}

bool Dlqr::LoadConfig(const std::string& configPath)
{
    YAML::Node lqrNode;
    try
    {
        lqrNode = YAML::LoadFile(configPath.c_str());
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to load: " << configPath << std::endl;
        return false;
    }
    _tuningMode = lqrNode["tuningMode"].as<bool>();
    if (_tuningMode)
    {
        LoadConfigLqrNode(lqrNode);
    }
    if(!calcGain()){
        return false;
    }
    return true;
}

Eigen::MatrixXd Dlqr::CalcGain(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B, const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R)
{
    int num_states = A.rows();
    const int MAX_RICCATI_ITERATIONS = 100;
    Eigen::MatrixXd P = Q;
    for (int i=MAX_RICCATI_ITERATIONS; i>0; i--){
        P = Q + A.transpose()*P*A-A.transpose()*P*B*(R+B.transpose()*P*B).inverse()*B.transpose()*P*A;
    }
    return (R+B.transpose()*P*B).inverse()*B.transpose()*P*A;
}

Eigen::MatrixXd Dlqr::CalcGain(DiscreteLtiStateSpace& sysd, const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R)
{
    Eigen::MatrixXd A = sysd.GetA();
    Eigen::MatrixXd B = sysd.GetB();
    return CalcGain(A, B, Q, R);
}

Eigen::MatrixXd Dlqr::GetGain()
{
    // TODO: Only calcGain() if there are control system parameter changes to speed up execution time
    calcGain();
    return _K;
}

bool Dlqr::calcGain()
{
    if (_pDiscreteSystem == NULL){
        _K = Eigen::MatrixXd::Zero(1,1);
        return false;
    }

    Eigen::MatrixXd Ad = _pDiscreteSystem->GetA();
    Eigen::MatrixXd Bd = _pDiscreteSystem->GetB();
    Eigen::MatrixXd P = _Q;

    for (int i=MAX_RICCATI_ITERATIONS; i>0; i--){
        P = _Q + Ad.transpose()*P*Ad-Ad.transpose()*P*Bd*(_R+Bd.transpose()*P*Bd).inverse()*Bd.transpose()*P*Ad;
    }
    _K = (_R+Bd.transpose()*P*Bd).inverse()*Bd.transpose()*P*Ad;
    
    // TODO: Check if gain is successful or not
    return true;
}

}
