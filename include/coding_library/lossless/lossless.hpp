#pragma once
#ifndef CL_LOSSLESS_HPP_
#define CL_LOSSLESS_HPP_

// Dictionary
#include "dictionary/byte_pair_coding/byte_pair_coding.hpp" // IWYU pragma: keep
#include "dictionary/lempel_ziv_77_coding.hpp"              // IWYU pragma: keep

// Entropy
#include "entropy/huffman/huffman.hpp" // IWYU pragma: keep

// Other
#include "other/burrows_wheeler_transform.hpp"           // IWYU pragma: keep
#include "other/move_to_front_transform.hpp"             // IWYU pragma: keep
#include "other/run_length_coding/run_length_coding.hpp" // IWYU pragma: keep

#endif