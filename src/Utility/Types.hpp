/*
 * POOSV 2020-21
 * Marco Antognini & Jamila Sam
 */

#ifndef INFOSV_TYPES_HPP
#define INFOSV_TYPES_HPP
#include <vector>
#include <utility>

/* A few typedefs */
using Angle      = double;
using Prob       = double;
using Probs      = std::vector<Prob>;
using Intervals  = std::vector<Angle>;
using RotationProbs = std::pair<Intervals, Probs>;
using Quantity   = double;
using Quantities = std::vector<Quantity>;
using Uid        = unsigned int; ///< Unique Identifier, @see createUid()
#endif // INFOSV_TYPES_HPP

