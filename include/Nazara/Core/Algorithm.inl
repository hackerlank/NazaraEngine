// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Core module"
// For conditions of distribution and use, see copyright notice in Config.hpp

// http://stackoverflow.com/questions/687490/c0x-how-do-i-expand-a-tuple-into-variadic-template-function-arguments
// Merci à Ryan "FullMetal Alchemist" Lahfa
// Merci aussi à Freedom de siteduzero.com

#include <Nazara/Core/Debug.hpp>

///TODO: Améliorer l'implémentation de UnpackTuple

template<unsigned int N>
struct NzImplTupleUnpack
{
	template <typename F, typename... ArgsT, typename... Args>
	void operator()(F func, const std::tuple<ArgsT...>& t,  Args&... args)
	{
		NzImplTupleUnpack<N-1>()(func, t, std::get<N-1>(t), args...);
	}
};

template<>
struct NzImplTupleUnpack<0>
{
	template <typename F, typename... ArgsT, typename... Args>
	void operator()(F func, const std::tuple<ArgsT...>&, Args&... args)
	{
		func(args...);
	}
};

// Algorithme venant de CityHash par Google
// http://stackoverflow.com/questions/8513911/how-to-create-a-good-hash-combine-with-64-bit-output-inspired-by-boosthash-co
template<typename T>
void NzHashCombine(std::size_t& seed, const T& v)
{
    const std::size_t kMul = 0x9ddfea08eb382d69ULL;

    std::hash<T> hasher;
    std::size_t a = (hasher(v) ^ seed) * kMul;
    a ^= (a >> 47);

    std::size_t b = (seed ^ a) * kMul;
    b ^= (b >> 47);

    seed = b * kMul;
}

template<typename F, typename... ArgsT>
void NzUnpackTuple(F func, const std::tuple<ArgsT...>& t)
{
	NzImplTupleUnpack<sizeof...(ArgsT)>()(func, t);
}

#include <Nazara/Core/DebugOff.hpp>