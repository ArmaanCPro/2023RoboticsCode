#include "vex.h"

namespace DS
{
  class Drive
  {
  public:
    Drive() = default;
    Drive(vex::motor_group& leftDrive, vex::motor_group& rightDrive)
    : m_LeftDrive(&leftDrive), m_RightDrive(&rightDrive) {}

    ~Drive()
    {
      m_LeftDrive = nullptr;
      m_RightDrive = nullptr;
    }

    inline void SpinFor(double rotation, vex::rotationUnits rotationUnits, bool leftReverse = false, bool rightReverse = false, bool blockExecution = false)
    {
      m_LeftDrive->spinFor(leftReverse ? reverse : forward, rotation, rotationUnits, blockExecution);
      m_RightDrive->spinFor(rightReverse ? reverse : forward, rotation, rotationUnits);
    }

    inline void SpinFor(double time, vex::timeUnits timeUnits, bool leftReverse = false, bool rightReverse = false)
    {
      m_LeftDrive->spinFor(leftReverse ? reverse : forward, time, timeUnits);
      m_RightDrive->spinFor(rightReverse ? reverse : forward, time, timeUnits);
    }

    inline void TurnFor(double time, vex::timeUnits timeUnits, bool leftReverse)
    {
      SpinFor(time, timeUnits, leftReverse, !leftReverse);
    }

    inline void TurnFor(double rotation, vex::rotationUnits rotationUnits, bool leftReverse, bool blockExecution)
    {
      SpinFor(rotation, rotationUnits, leftReverse, !leftReverse, blockExecution);
    }

    // Spins forward unless either leftReverse or rightReverse are true
    inline void Spin(double velocity, vex::percentUnits percentUnits, bool leftReverse = false, bool rightReverse = false)
    {
      m_LeftDrive->spin(leftReverse ? reverse : forward, velocity, percentUnits);
      m_RightDrive->spin(rightReverse ? reverse : forward, velocity, percentUnits);
    }

    inline void Turn(double velocity, vex::percentUnits percentUnits, bool leftReverse)
    {
      Spin(velocity, percentUnits, leftReverse, !leftReverse);
    }

  protected:
    vex::motor_group* m_LeftDrive;
    vex::motor_group* m_RightDrive;
  };
}