﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_MACROS_CONSTEXPR_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_MACROS_CONSTEXPR_HPP

/* Character Code : UTF-8 (BOM) */
/* Bug Check : already checked */
/* Android NDK Compile (Clang 5.0) : already checked */

#ifndef DTL_VERSIONING_CPP14_CONSTEXPR

#if defined(_MSC_VER)

#if (_MSC_VER <= 1900)
#define DTL_VERSIONING_CPP14_CONSTEXPR

#elif defined(_MSC_VER) && defined(_MSVC_LANG)
#if (_MSVC_LANG >= 201402L)
#define DTL_VERSIONING_CPP14_CONSTEXPR constexpr
#endif
#endif

#elif defined(__cplusplus)

#if (__cplusplus >= 201402L)
#define DTL_VERSIONING_CPP14_CONSTEXPR constexpr
#endif

#endif

#endif

///// もしDTL_VERSIONING_CPP14_CONSTEXPRが無かったらつくる /////
#ifndef DTL_VERSIONING_CPP14_CONSTEXPR
#define DTL_VERSIONING_CPP14_CONSTEXPR
#endif

#endif //Included Dungeon Template Library