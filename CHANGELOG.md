# CHANGELOG

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased] 

## [1.1.2] - 2024-12-16

- Remove compatibility header for old name of driver class, as it breaks on non-case-sensitive systems

## [1.1.1] - 2024-12-05

- Compatibility header for old name SensirionI2CSht4x

## [1.1.0] - 2024-4-10

### Changed
- Naming updated: SensirionI2CSht4x is now SensirionI2cSht4x (note case change for I2c)

### Fixed
- Fix colliding definitions with other Sensirion sensor drivers


## [1.0.0] - 2024-3-14

### Changed

- Defined I2C addresses for different sensor models. You must now pass the I2C address to use in the begin() method of SensirionI2cSht4x
- Improved README
## [0.1.0] - 2021-7-27

### Added

- Add product picture
- Add interfaces to start, stop and read measurements.
- Add interfaces to read product name, serial number and version

[Unreleased]: https://github.com/Sensirion/arduino-i2c-sht4x/compare/1.1.0...HEAD
[1.1.0]: https://github.com/Sensirion/arduino-i2c-sht4x/compare/1.0.0...1.1.0
[1.0.0]: https://github.com/Sensirion/arduino-i2c-sht4x/compare/0.1.0...1.0.0
[0.1.0]: https://github.com/Sensirion/arduino-i2c-sht4x/releases/tag/0.1.0