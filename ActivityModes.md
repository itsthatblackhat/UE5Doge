# Activity Modes System Documentation

## Overview

The Activity Modes system in **Ready Player Doge** allows players to engage in various activities, each with unique controls, HUD elements, animations, and interactions. This system is designed to be flexible, scalable, and maintainable, ensuring a seamless player experience.

## File Structure

### Enumerations
- **EPlayerActivityMode.h**: Defines all possible player activity modes.

### State Management
- **PlayerStateManager.h/cpp**: Manages transitions and behaviors associated with different activity modes.

### Player Character Integration
- **ReadyPlayerDogeCharacter.h/cpp**: Integrates the `PlayerStateManager` and manages activity mode transitions.

### HUD Management
- **ReadyPlayerDogeHUD.h/cpp**: Manages dynamic HUD elements based on the current activity mode.
- **BP_ReadyPlayerDogeHUD.uasset**: Blueprint for the HUD layout.

### Input Handling
- **EnhancedInputComponent.h/cpp**: (Optional) Handles dynamic input bindings based on activity modes.

### Animation Blueprints
- **PlayerAnimInstance.h/cpp**: Manages animations based on the current activity mode.
- **BP_PlayerAnimInstance.uasset**: Animation Blueprint linked to `UPlayerAnimInstance`.

### UI Widgets
- **ActivityModeWidget.h/cpp**: Displays activity-specific UI elements.
- **BP_ActivityModeWidget.uasset**: Blueprint for the activity mode UI widget.

### Configuration and Settings
- **ActivityModeSettings.ini**: Configuration file defining settings for each activity mode.
- **PlayerModeConfig.h/cpp**: Loads and provides access to activity mode settings.

### Activity Mode Handlers
- **ActivityModeHandler.h**: Interface for activity mode handlers.
- **WalkingModeHandler.h/cpp**: Example handler for the Walking mode.

## Adding a New Activity Mode

1. **Define the Mode:**
   - Add a new entry to `EPlayerActivityMode.h`.

2. **Create a Handler (Optional):**
   - Implement a new handler class inheriting from `IActivityModeHandler`.

3. **Update Configuration:**
   - Add settings for the new mode in `ActivityModeSettings.ini`.
   - Update `PlayerModeConfig` to load these settings.

4. **Integrate with State Manager:**
   - Modify `PlayerStateManager.cpp` to handle the new mode in `OnModeEnter` and `OnModeExit`.

5. **Update HUD:**
   - Modify `ActivityModeWidget.cpp` and `BP_ActivityModeWidget` to display UI elements for the new mode.

6. **Bind Inputs:**
   - Update `EnhancedInputComponent.cpp` to bind inputs specific to the new mode.

7. **Update Animations:**
   - Add animation states and transitions in `BP_PlayerAnimInstance`.

8. **Test Thoroughly:**
   - Ensure smooth transitions and correct behavior across systems.

## Best Practices

- **Modular Design:** Keep each component isolated to facilitate easy updates and additions.
- **Event-Driven Updates:** Use events or delegates to synchronize mode changes across systems.
- **Blueprint Integration:** Expose necessary properties and functions to Blueprints for flexibility.
- **Consistent Naming:** Follow consistent naming conventions for clarity and maintainability.
- **Documentation:** Maintain comprehensive documentation to assist future development and onboarding.

## Troubleshooting

- **HUD Not Updating:** Ensure `UpdateHUDForMode` is correctly called and that the HUD widget is properly referenced.
- **Input Not Responding:** Verify that inputs are correctly bound in `EnhancedInputComponent` and that the appropriate mode is active.
- **Animations Not Playing:** Check that `PlayerAnimInstance` correctly receives the current activity mode and that animation states are properly set up in the Animation Blueprint.
- **Mode Transitions Fail:** Ensure `CanChangeMode` logic permits the desired transition and that handlers are correctly implemented.

---

For further assistance or questions, please refer to the project's main documentation or contact the development team.

