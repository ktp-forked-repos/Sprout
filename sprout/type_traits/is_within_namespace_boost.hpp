/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_BOOST_HPP
#define SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_BOOST_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl sprout_adl_tester_namespace_boost(...);
}	// namespace sprout_adl

namespace boost {
	template<typename T>
	void sprout_adl_tester_namespace_boost(T&&);
}	// namespace boost

namespace sprout_adl_tester_detail {
	using sprout_adl::sprout_adl_tester_namespace_boost;

	template<typename T>
	struct is_within_namespace_boost_test {
	public:
		template<
			typename U = T,
			typename R = typename sprout::identity<decltype(sprout_adl_tester_namespace_boost(std::declval<U>()))>::type
		>
		static sprout::is_found_via_adl<R> test(int);
		static sprout::false_type test(...);
	};
}	// namespace sprout_adl_tester_detail

namespace sprout {
#if defined(_MSC_VER) && (_MSC_VER > 1900)
	template<typename T, typename Base_ = typename sprout::identity<decltype(sprout_adl_tester_detail::is_within_namespace_boost_test<T>::test(0))>::type>
	struct is_within_namespace_boost
		: public Base_
	{};
#else
	template<typename T>
	struct is_within_namespace_boost
		: public sprout::identity<decltype(sprout_adl_tester_detail::is_within_namespace_boost_test<T>::test(0))>::type
	{};
#endif

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_within_namespace_boost_v = sprout::is_within_namespace_boost<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_BOOST_HPP
