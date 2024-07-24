#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

enum ControllerCommand {
  CROSS,
  CIRCLE,
  SQUARE,
  TRIANGLE,
  LEFT,
  UP,
  RIGHT,
  DOWN,
  R1,
  R2,
  R3,
  L1,
  L2,
  L3,
  OPTIONS,
  SHARE,
  PS_BUTTON,
  ANALOG_LEFT_X,
  ANALOG_LEFT_Y,
  ANALOG_RIGHT_X,
  ANALOG_RIGHT_Y,
};

class ControllerState {
private:
  bool buttonCross, buttonCircle, buttonSquare, buttonTriangle;
  bool buttonLeft, buttonUp, buttonRight, buttonDown;
  bool buttonR1, buttonR2, buttonR3, buttonL1, buttonL2, buttonL3;
  bool buttonStart, buttonSelect, buttonPs;
  int analogLeftX, analogLeftY, analogRightX, analogRightY;
  int touchpad;

  void onButtonChange(ControllerCommand command, bool newState) {
    Serial.print(newState ? "PRESS " : "RELEASE ");
    Serial.println(getCommandId(command));
  }

  void onAnalogChange(ControllerCommand command, int newX, int newY) {
    Serial.print("MOVE ");
    Serial.print(getCommandId(command));
    Serial.print(" X: ");
    Serial.print(newX);
    Serial.print(" Y: ");
    Serial.println(newY);
  }

public:
  ControllerState()
    : buttonCross(false), buttonCircle(false), buttonSquare(false), buttonTriangle(false),
      buttonLeft(false), buttonUp(false), buttonRight(false), buttonDown(false),
      buttonR1(false), buttonR2(false), buttonR3(false), buttonL1(false), buttonL2(false), buttonL3(false),
      buttonStart(false), buttonSelect(false), buttonPs(false),
      analogLeftX(0), analogLeftY(0), analogRightX(0), analogRightY(0), touchpad(0) {}

  const char* getCommandId(ControllerCommand buttonType) {
    switch (buttonType) {
      case ControllerCommand::CROSS: return "1";
      case ControllerCommand::CIRCLE: return "2";
      case ControllerCommand::SQUARE: return "3";
      case ControllerCommand::TRIANGLE: return "4";

      case ControllerCommand::L1: return "5";
      case ControllerCommand::R1: return "6";
      case ControllerCommand::L2: return "7";
      case ControllerCommand::R2: return "8";

      case ControllerCommand::SHARE: return "9";
      case ControllerCommand::OPTIONS: return "10";

      case ControllerCommand::L3: return "11";
      case ControllerCommand::R3: return "12";

      case ControllerCommand::UP: return "13";
      case ControllerCommand::DOWN: return "14";
      case ControllerCommand::LEFT: return "15";
      case ControllerCommand::RIGHT: return "16";

      case ControllerCommand::PS_BUTTON: return "17";
      case ControllerCommand::ANALOG_LEFT_X: return "Left Stick X";
      case ControllerCommand::ANALOG_LEFT_Y: return "Left Stick Y";
      case ControllerCommand::ANALOG_RIGHT_X: return "Right Stick X";
      case ControllerCommand::ANALOG_RIGHT_Y: return "Right Stick Y";
      default: return "Unknown";
    }
  }

  void setButtonCross(bool value) {
    if (buttonCross != value) {
      buttonCross = value;
      onButtonChange(ControllerCommand::CROSS, value);
    }
  }
  void setButtonCircle(bool value) {
    if (buttonCircle != value) {
      buttonCircle = value;
      onButtonChange(ControllerCommand::CIRCLE, value);
    }
  }
  void setButtonSquare(bool value) {
    if (buttonSquare != value) {
      buttonSquare = value;
      onButtonChange(ControllerCommand::SQUARE, value);
    }
  }
  void setButtonTriangle(bool value) {
    if (buttonTriangle != value) {
      buttonTriangle = value;
      onButtonChange(ControllerCommand::TRIANGLE, value);
    }
  }
  void setButtonLeft(bool value) {
    if (buttonLeft != value) {
      buttonLeft = value;
      onButtonChange(ControllerCommand::LEFT, value);
    }
  }
  void setButtonUp(bool value) {
    if (buttonUp != value) {
      buttonUp = value;
      onButtonChange(ControllerCommand::UP, value);
    }
  }
  void setButtonRight(bool value) {
    if (buttonRight != value) {
      buttonRight = value;
      onButtonChange(ControllerCommand::RIGHT, value);
    }
  }
  void setButtonDown(bool value) {
    if (buttonDown != value) {
      buttonDown = value;
      onButtonChange(ControllerCommand::DOWN, value);
    }
  }
  void setButtonR1(bool value) {
    if (buttonR1 != value) {
      buttonR1 = value;
      onButtonChange(ControllerCommand::R1, value);
    }
  }
  void setButtonR2(bool value) {
    if (buttonR2 != value) {
      buttonR2 = value;
      onButtonChange(ControllerCommand::R2, value);
    }
  }
  void setButtonR3(bool value) {
    if (buttonR3 != value) {
      buttonR3 = value;
      onButtonChange(ControllerCommand::R3, value);
    }
  }
  void setButtonL1(bool value) {
    if (buttonL1 != value) {
      buttonL1 = value;
      onButtonChange(ControllerCommand::L1, value);
    }
  }
  void setButtonL2(bool value) {
    if (buttonL2 != value) {
      buttonL2 = value;
      onButtonChange(ControllerCommand::L2, value);
    }
  }
  void setButtonL3(bool value) {
    if (buttonL3 != value) {
      buttonL3 = value;
      onButtonChange(ControllerCommand::L3, value);
    }
  }
  void setButtonStart(bool value) {
    if (buttonStart != value) {
      buttonStart = value;
      onButtonChange(ControllerCommand::OPTIONS, value);
    }
  }
  void setButtonSelect(bool value) {
    if (buttonSelect != value) {
      buttonSelect = value;
      onButtonChange(ControllerCommand::SHARE, value);
    }
  }
  void setButtonPs(bool value) {
    if (buttonPs != value) {
      buttonPs = value;
      onButtonChange(ControllerCommand::PS_BUTTON, value);
    }
  }

  void setAnalogLeftX(int value) {
    if (analogLeftX != value) {
      analogLeftX = value;
      onAnalogChange(ControllerCommand::ANALOG_LEFT_X, value, analogLeftY);
    }
  }
  void setAnalogLeftY(int value) {
    if (analogLeftY != value) {
      analogLeftY = value;
      onAnalogChange(ControllerCommand::ANALOG_LEFT_Y, analogLeftX, value);
    }
  }
  void setAnalogRightX(int value) {
    if (analogRightX != value) {
      analogRightX = value;
      onAnalogChange(ControllerCommand::ANALOG_RIGHT_X, value, analogRightY);
    }
  }
  void setAnalogRightY(int value) {
    if (analogRightY != value) {
      analogRightY = value;
      onAnalogChange(ControllerCommand::ANALOG_RIGHT_Y, analogRightX, value);
    }
  }
  void setTouchpad(int value) {
    if (touchpad != value) {
      touchpad = value;
      Serial.print("Touchpad changed: ");
      Serial.println(value);
    }
  }
};

#endif