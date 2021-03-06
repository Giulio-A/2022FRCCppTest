// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/DriverStation.h>
#include <frc/XboxController.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>

#include <cmath>
#include <iostream>

namespace WestCoastConstants {
  //PI
  const double kPI = 3.14159265358979;
  
  // Motor Ports
  const int kLeftLeader = 1;
  const int kRightLeader = 4;
  const int kLeftFollower = 2;
  const int kRightFollower = 3;

  //Drive With Controller Constants
  const double kFullSpeedMult = 0.75;
  const double kFullRotationMult = 0.50;
  const double kHalfSpeedMult = 0.50;
  const double kHalfRotationMult = 0.35;

  // Calibration Values

  // Motor Max Speeds
  
  // Encoder Values
  const int kPulsesPerRev = 2048;

  // Sizes
  //In Inches
  const double kWheelDiameter = 6.0;
}
class WestCoastDrive : public frc2::SubsystemBase {
 public:
  WestCoastDrive(frc::XboxController* p_Controller);

  void arcadeDrive(double speed, double rotation);
  void controllerDrive();
  void toggleDriveMode();
  void zeroDrivetrain();
  
  double getAvgEncoderPosition();

  void setAutoState(bool state) {
    m_AutoState = state;
  }

  bool getAutoState() {
    return m_AutoState;
  }

  void Periodic() override;

 private:

  bool m_AutoState;
  // true = full speed
  // false = half speed
  bool m_DriveMode;

  frc::XboxController* mp_Controller;
  double m_ControllerDriveSpeed;
  double m_ControllerDriveRotation;
  double m_DriveSpeedMult;
  double m_RotationSpeedMult;

  WPI_TalonFX m_LeftLeader{WestCoastConstants::kLeftLeader};
  WPI_TalonFX m_RightLeader{WestCoastConstants::kRightLeader};
  WPI_TalonFX m_LeftFollower{WestCoastConstants::kLeftFollower};
  WPI_TalonFX m_RightFollower{WestCoastConstants::kRightFollower};

  frc::MotorControllerGroup m_LeftGroup{m_LeftLeader, m_LeftFollower};
  frc::MotorControllerGroup m_RightGroup{m_RightLeader, m_RightFollower};

  frc::DifferentialDrive m_DifferntialDrive{m_LeftGroup, m_RightGroup};
};
