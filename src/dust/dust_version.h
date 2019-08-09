#ifndef DUST_VERSION_H
#define DUST_VERSION_H

#include <string>

// Increase with every consensus affecting change
#define DUST_VERSION_MAJOR   9

// Increase with every non-consensus affecting feature
#define DUST_VERSION_MINOR   1

// Increase with every patch, which is not a feature or consensus affecting
#define DUST_VERSION_PATCH   0

// Use "-dev" for development versions, switch to "-rel" for tags
#define DUST_VERSION_TYPE    "-rel"


//! Dust client version
static const int DUST_VERSION =
                        +  100000 * DUST_VERSION_MAJOR
                        +     100 * DUST_VERSION_MINOR
                        +       1 * DUST_VERSION_PATCH;

//! Returns formatted Dust version, e.g. "0.0.9.1-dev"
const std::string DustVersion();

//! Returns formatted Bitsend Core version, e.g. "0.10", "0.9.3"
const std::string BitsendCoreVersion();

//! Returns build date
const std::string BuildDate();

//! Returns commit identifier, if available
const std::string BuildCommit();

#endif // DUST_VERSION_H
