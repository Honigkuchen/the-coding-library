#pragma once
#ifndef CL_LOSSLESS_HPP_
#define CL_LOSSLESS_HPP_

// Dictionary
#include "dictionary/byte_pair_coding/byte_pair_coding.hpp"
#include "dictionary/lempel_ziv_77_coding.hpp"

// Entropy
#include "entropy/huffman/huffman.hpp"

// Other
#include "other/burrows_wheeler_transform.hpp"
#include "other/move_to_front_transform.hpp"
#include "other/run_length_coding/run_length_coding.hpp"

#endif