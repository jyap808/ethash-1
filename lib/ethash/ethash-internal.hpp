// Copyright 2018 Pawel Bylica.
// Licensed under the Apache License, Version 2.0. See the LICENSE file.

/// @file
/// Contains declarations of internal ethash functions to allow them to be
/// unit-tested.

#pragma once

#include <ethash/ethash.hpp>

#include <memory>
#include <vector>

namespace ethash
{
union hash512
{
    uint64_t words[8] = {
        0,
    };
    uint32_t half_words[16];
    char bytes[64];
};

union hash1024
{
    // TODO: Is the array worse than 2 fields for memory aliasing?
    hash512 hashes[2];
    uint64_t words[16];
    uint32_t hwords[32];
    char bytes[128];

    constexpr hash1024() : hashes{{}, {}} {}
};

/**
 * Coverts the number of items of a light cache to size in bytes.
 *
 * @param num_items  The number of items in the light cache.
 * @return           The size of the light cache in bytes.
 */
inline size_t get_light_cache_size(int num_items) noexcept
{
    return static_cast<size_t>(num_items) * light_cache_item_size;
}

/**
 * Coverts the number of items of a full dataset to size in bytes.
 *
 * @param num_items  The number of items in the full dataset.
 * @return           The size of the full dataset in bytes.
 */
inline uint64_t get_full_dataset_size(int num_items) noexcept
{
    return static_cast<uint64_t>(num_items) * full_dataset_item_size;
}

hash256 calculate_seed(int epoch_number) noexcept;

void build_light_cache(hash512 cache[], int num_items, const hash256 &seed);

hash1024 calculate_dataset_item(const ethash_epoch_context& context, size_t index) noexcept;

hash512 calculate_dataset_item_partial(const hash512* cache, int num_cache_items, size_t index) noexcept;
}

extern "C" struct ethash_epoch_context
{
    int epoch_number = -1;
    int light_cache_num_items = 0;
    ethash::hash512* light_cache = nullptr;
    int full_dataset_num_items = 0;
    ethash::hash1024* full_dataset = nullptr;
};