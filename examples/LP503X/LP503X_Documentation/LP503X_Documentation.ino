//  Produced by Dinura Pasan in November 2023 and distributed free of charge.
//  Controlling LP5030, LP5036 constant current RGB LED driver IC from within Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

// LP5030 product page -> https://www.ti.com/product/LP5030
// LP5036 product page -> https://www.ti.com/product/LP5036
// Datasheet -> https://www.ti.com/lit/gpn/lp5036


//*********** LP503X Library Documentation ***********//

// The LP503X library is a collection of functions designed to control and manage LED lighting using the LP503X LED driver integrated circuit. This library facilitates various operations such as setting LED colors, managing brightness levels, enabling or disabling PWM dithering, configuring maximum LED current, and toggling between standby and normal operational modes. Additionally, it provides a utility function to print the current settings for debugging and monitoring purposes. Overall, the LP503X library offers a comprehensive set of functionalities to efficiently control and customize LED lighting using the LP503X driver IC in embedded systems or similar applications.

// ### LP503X::LP503X(uint8_t I2C_ADDR)
// - **Description**: Constructor for the LP503X class, initializing the I2C address.
// - **Parameters**: `I2C_ADDR` - the I2C address of the LP503X IC.

// ### void LP503X::setColour(uint8_t LED, uint8_t value)
// - **Description**: Sets the color mixing level of an individual LED output.
// - **Parameters**: `LED` - LED output pin number, `value` - Color mixing level (0-255).

// ### uint8_t LP503X::getColour(uint8_t LED)
// - **Description**: Retrieves the color mixing level of a specific LED output.
// - **Parameters**: `LED` - LED output pin number.
// - **Returns**: Color mixing level (0-255).

// ### void LP503X::setBrightness(uint8_t LED, uint8_t value)
// - **Description**: Sets the intensity level of an individual LED output channel.
// - **Parameters**: `LED` - LED output pin number, `value` - Intensity level (0-255).

// ### uint8_t LP503X::getBrightness(uint8_t LED)
// - **Description**: Retrieves the intensity level of a specific LED output channel.
// - **Parameters**: `LED` - LED output pin number.
// - **Returns**: Intensity level (0-255).

// ### void LP503X::resetRegisters()
// - **Description**: Resets all internal register values in the LP503X IC to default.

// ### void LP503X::setRGBbank(char colour, uint8_t value, uint8_t intensity)
// - **Description**: Sets the color mixing level and intensity of an LED bank.
// - **Parameters**: `colour` - LED bank color (R/G/B), `value` - Color mixing level, `intensity` - Intensity level.

// ### void LP503X::setRGBbank(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity)
// - **Description**: Sets the color mixing levels of all RGB LED banks simultaneously.
// - **Parameters**: `red`, `green`, `blue` - Color mixing levels for respective banks, `intensity` - Intensity level.

// ### uint8_t LP503X::getBankColour(char colour)
// - **Description**: Retrieves the color mixing level of a specific LED bank.
// - **Parameters**: `colour` - LED bank color (R/G/B).
// - **Returns**: Color mixing level (0-255).

// ### uint8_t LP503X::getBankIntensity()
// - **Description**: Retrieves the intensity level of all LED banks.
// - **Returns**: Intensity level (0-255).

// ### void LP503X::printGrapics()
// - **Description**: Displays the status of all LED outputs (color mixing and intensity).

// ### void LP503X::printBank()
// - **Description**: Displays the status of all LED banks (color mixing and intensity).

// ### void LP503X::setModule(uint8_t moduleID, bool enable)
// - **Description**: Enables or disables a specific LED module for LED bank control.
// - **Parameters**: `moduleID` - ID of the LED module, `enable` - Enable or disable.

// ### bool LP503X::getModule(uint8_t moduleID)
// - **Description**: Checks if a specific LED module is enabled for LED bank control.
// - **Parameters**: `moduleID` - ID of the LED module.
// - **Returns**: Whether the module is enabled or disabled.

// ### void LP503X::printModule()
// - **Description**: Displays the current state of LED modules.

// ### void LP503X::logScale(bool status)
// - **Description**: Sets the light dimming curve (logarithmic or linear).
// - **Parameters**: `status` - Logarithmic or linear scale.

// ### bool LP503X::logScale()
// - **Description**: Checks the currently activated light dimming curve.
// - **Returns**: Logarithmic or linear scale status.

// ### void LP503X::Shutdown(bool status)
// - **Description**: Shuts down or activates all LEDs.
// - **Parameters**: `status` - Shutdown or normal operation.

// ### bool LP503X::Shutdown()
// - **Description**: Checks if all LEDs are shut down.
// - **Returns**: Shutdown or normal operation status.

// ### void LP503X::powerSave(bool status)
// - **Description**: Enables or disables automatic power-saving mode.
// - **Parameters**: `status` - Enable or disable power-saving mode.

// ### bool LP503X::powerSave()
// - **Description**: Checks if automatic power-saving mode is enabled or disabled.
// - **Returns**: Power-saving mode status.

// ### void LP503X::autoIncrement(bool status)
// - **Description**: Enables or disables auto-increment feature for the LP503X device.
// - **Parameters**: `status` - Enable or disable auto-increment.

// ### bool LP503X::autoIncrement()
// - **Description**: Checks if auto-increment feature is enabled or disabled.
// - **Returns**: Auto-increment status.

// ### void LP503X::PWM_Dithering(bool status)
// - **Description**: Enables or disables PWM dithering. PWM dithering is a technique used to reduce color banding in low-bit-depth color systems.
// - **Parameters**: `status` - Enable or disable PWM dithering.

// ### bool LP503X::PWM_Dithering()
// - **Description**: Checks if PWM dithering is enabled or disabled.
// - **Returns**: PWM dithering status.

// ### void LP503X::maxCurrent(bool status)
// - **Description**: Sets the maximum current for the LEDs.
// - **Parameters**: `status` - Enable or disable setting the maximum current.

// ### bool LP503X::maxCurrent()
// - **Description**: Checks if the setting for maximum current is enabled or disabled.
// - **Returns**: Maximum current setting status.

// ### void LP503X::standby_mode()
// - **Description**: Puts the LP503X IC into standby mode. Standby mode significantly reduces power consumption but keeps the I2C interface active.

// ### void LP503X::normal_mode()
// - **Description**: Wakes up the LP503X IC from standby mode and returns to normal operation.

// ### void LP503X::print_Settings()
// - **Description**: Prints the current settings of the LP503X IC, including various configurations, statuses, and modes. This function is used for debugging or monitoring purposes to observe the current setup and configurations.