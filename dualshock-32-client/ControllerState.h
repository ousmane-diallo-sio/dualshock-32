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
    Serial.print(getCommandName(command));
    // Serial.println(newState ? " pressed" : " released");
  }

  void onAnalogChange(ControllerCommand command, int newX, int newY) {
    Serial.print(getCommandName(command));
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

  const char* getCommandName(ControllerCommand buttonType) {
    switch (buttonType) {
      case CROSS: return "Cross";
      case CIRCLE: return "Circle";
      case SQUARE: return "Square";
      case TRIANGLE: return "Triangle";
      case LEFT: return "Left";
      case UP: return "Up";
      case RIGHT: return "Right";
      case DOWN: return "Down";
      case R1: return "R1";
      case R2: return "R2";
      case R3: return "R3";
      case L1: return "L1";
      case L2: return "L2";
      case L3: return "L3";
      case OPTIONS: return "Options";
      case SHARE: return "Share";
      case PS_BUTTON: return "PS Button";
      case LEFT_STICK: return "Left Stick";
      case RIGHT_STICK: return "Right Stick";
      default: return "Unknown";
    }
  }

  void setButtonCross(bool value) {
    if (buttonCross != value) {
      buttonCross = value;
      onButtonChange("Cross", value);
    }
  }
  void setButtonCircle(bool value) {
    if (buttonCircle != value) {
      buttonCircle = value;
      onButtonChange("Circle", value);
    }
  }
  void setButtonSquare(bool value) {
    if (buttonSquare != value) {
      buttonSquare = value;
      onButtonChange("Square", value);
    }
  }
  void setButtonTriangle(bool value) {
    if (buttonTriangle != value) {
      buttonTriangle = value;
      onButtonChange("Triangle", value);
    }
  }
  void setButtonLeft(bool value) {
    if (buttonLeft != value) {
      buttonLeft = value;
      onButtonChange("Left", value);
    }
  }
  void setButtonUp(bool value) {
    if (buttonUp != value) {
      buttonUp = value;
      onButtonChange("Up", value);
    }
  }
  void setButtonRight(bool value) {
    if (buttonRight != value) {
      buttonRight = value;
      onButtonChange("Right", value);
    }
  }
  void setButtonDown(bool value) {
    if (buttonDown != value) {
      buttonDown = value;
      onButtonChange("Down", value);
    }
  }
  void setButtonR1(bool value) {
    if (buttonR1 != value) {
      buttonR1 = value;
      onButtonChange("R1", value);
    }
  }
  void setButtonR2(bool value) {
    if (buttonR2 != value) {
      buttonR2 = value;
      onButtonChange("R2", value);
    }
  }
  void setButtonR3(bool value) {
    if (buttonR3 != value) {
      buttonR3 = value;
      onButtonChange("R3", value);
    }
  }
  void setButtonL1(bool value) {
    if (buttonL1 != value) {
      buttonL1 = value;
      onButtonChange("L1", value);
    }
  }
  void setButtonL2(bool value) {
    if (buttonL2 != value) {
      buttonL2 = value;
      onButtonChange("L2", value);
    }
  }
  void setButtonL3(bool value) {
    if (buttonL3 != value) {
      buttonL3 = value;
      onButtonChange("L3", value);
    }
  }
  void setButtonStart(bool value) {
    if (buttonStart != value) {
      buttonStart = value;
      onButtonChange("Options", value);
    }
  }
  void setButtonSelect(bool value) {
    if (buttonSelect != value) {
      buttonSelect = value;
      onButtonChange("Select", value);
    }
  }
  void setButtonPs(bool value) {
    if (buttonPs != value) {
      buttonPs = value;
      onButtonChange("PS", value);
    }
  }

  void setAnalogLeftX(int value) {
    if (analogLeftX != value) {
      analogLeftX = value;
      onAnalogChange("Left Stick", value, analogLeftY);
    }
  }
  void setAnalogLeftY(int value) {
    if (analogLeftY != value) {
      analogLeftY = value;
      onAnalogChange("Left Stick", analogLeftX, value);
    }
  }
  void setAnalogRightX(int value) {
    if (analogRightX != value) {
      analogRightX = value;
      onAnalogChange("Right Stick", value, analogRightY);
    }
  }
  void setAnalogRightY(int value) {
    if (analogRightY != value) {
      analogRightY = value;
      onAnalogChange(ANALOG_RIGHT_Y, analogRightX, value);
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