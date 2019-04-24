﻿/*#######################################################################################
	Made by Kasugaccho
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	This code is licensed under CC0.
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_UTILITY_REPLACE_SOME
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_UTILITY_REPLACE_SOME

/* Character Code : UTF-8 (BOM) */
/* Bug Check : already checked */
/* Android NDK Compile (Clang 5.0) : already checked */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>
#include <algorithm>
#include <Base/Struct.hpp>

namespace dtl {
	inline namespace shape {

		//マスを指定した数値で埋める
		template<typename Matrix_Int_>
		class ReplaceSome {
		private:


			///// エイリアス /////

			using Index_Size = std::size_t;
			using PairSize = std::pair<Index_Size, Index_Size>;


			///// メンバ変数 /////

			Index_Size point_x{};
			Index_Size point_y{};
			Index_Size width{};
			Index_Size height{};
			Matrix_Int_ after_value{};
			std::vector<Matrix_Int_> before_value{};
			std::size_t replace_num{};

			constexpr void string_String() const noexcept {}
			template<typename Int_, typename ...Args_>
			constexpr void string_String(const Int_& first_, const Args_& ... args_) noexcept {
				this->before_value.emplace_back(static_cast<Matrix_Int_>(first_));
				this->string_String(args_...);
			}


			///// 代入処理 /////

			template<typename Matrix_>
			constexpr inline void substitutionSTL(Matrix_&& matrix_, std::vector<std::pair<std::size_t, std::size_t>>& value_pairs, const Index_Size point_x_, const Index_Size point_y_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_]) {
						value_pairs.emplace_back(std::make_pair(point_y_, point_x_));
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_>
			constexpr inline void substitutionArray(Matrix_&& matrix_, std::vector<std::pair<std::size_t, std::size_t>>& value_pairs, const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_ * max_x_ + point_x_]) {
						value_pairs.emplace_back(std::make_pair(point_y_, point_x_));
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_ * max_x_ + point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_>
			constexpr inline void substitutionLayer(Matrix_ && matrix_, std::vector<std::pair<std::size_t, std::size_t>>& value_pairs, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_][layer_]) {
						value_pairs.emplace_back(std::make_pair(point_y_, point_x_));
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_][layer_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}

			template<typename Matrix_, typename Function_>
			constexpr inline void substitutionSTL(Matrix_ && matrix_, std::vector<std::pair<std::size_t, std::size_t>>& value_pairs, const Index_Size point_x_, const Index_Size point_y_, Function_ && function_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_] && function_(matrix_[point_y_][point_x_])) {
						value_pairs.emplace_back(std::make_pair(point_y_, point_x_));
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_, typename Function_>
			constexpr inline void substitutionArray(Matrix_ && matrix_, std::vector<std::pair<std::size_t, std::size_t>>& value_pairs, const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_, Function_ && function_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_ * max_x_ + point_x_] && function_(matrix_[point_y_ * max_x_ + point_x_])) {
						value_pairs.emplace_back(std::make_pair(point_y_, point_x_));
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_ * max_x_ + point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_, typename Function_>
			constexpr inline void substitutionLayer(Matrix_ && matrix_, std::vector<std::pair<std::size_t, std::size_t>>& value_pairs, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_, Function_ && function_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_][layer_] && function_(matrix_[point_y_][point_x_][layer_])) {
						value_pairs.emplace_back(std::make_pair(point_y_, point_x_));
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_][layer_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_>
			bool drawSTL(Matrix_&& matrix_, const Index_Size point_y_, Args_&& ... args_) const noexcept {
				if (this->replace_num == 0) return true;
				if (this->before_value.size() == 0) return false;

				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (Index_Size row{ this->point_y }; row < point_y_; ++row)
					for (Index_Size col{ this->point_x }; col < matrix_[row].size(); ++col)
						this->substitutionSTL(matrix_, value_pairs, col, row, args_...);
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (this->replace_num >= value_pairs.size()) {
					for (const auto& i : value_pairs)
						matrix_[i.first][i.second] = this->after_value;
					return true;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first][value_pairs[index].second] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			bool drawWidthSTL(Matrix_ && matrix_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
				if (this->replace_num == 0) return true;
				if (this->before_value.size() == 0) return false;

				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (Index_Size row{ this->point_y }; row < point_y_; ++row)
					for (Index_Size col{ this->point_x }; col < matrix_[row].size() && col < point_x_; ++col)
						this->substitutionSTL(matrix_, value_pairs, col, row, args_...);
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (this->replace_num >= value_pairs.size()) {
					for (const auto& i : value_pairs)
						matrix_[i.first][i.second] = this->after_value;
					return true;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first][value_pairs[index].second] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}
				return true;
			}

			//LayerSTL
			template<typename Matrix_, typename ...Args_>
			bool drawLayerSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
				if (this->replace_num == 0) return true;
				if (this->before_value.size() == 0) return false;

				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (Index_Size row{ this->point_y }; row < point_y_; ++row)
					for (Index_Size col{ this->point_x }; col < matrix_[row].size(); ++col)
						this->substitutionLayer(matrix_, value_pairs, layer_, col, row, args_...);
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (this->replace_num >= value_pairs.size()) {
					for (const auto& i : value_pairs)
						matrix_[i.first][i.second][layer_] = this->after_value;
					return true;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first][value_pairs[index].second][layer_] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			bool drawLayerWidthSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
				if (this->replace_num == 0) return true;
				if (this->before_value.size() == 0) return false;

				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (Index_Size row{ this->point_y }; row < point_y_; ++row)
					for (Index_Size col{ this->point_x }; col < matrix_[row].size() && col < point_x_; ++col)
						this->substitutionLayer(matrix_, value_pairs, layer_, col, row, args_...);
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (this->replace_num >= value_pairs.size()) {
					for (const auto& i : value_pairs)
						matrix_[i.first][i.second][layer_] = this->after_value;
					return true;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first][value_pairs[index].second] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first][value_pairs[index].second][layer_] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			bool drawNormal(Matrix_ && matrix_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
				if (this->replace_num == 0) return true;
				if (this->before_value.size() == 0) return false;

				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (Index_Size row{ this->point_y }; row < point_y_; ++row)
					for (Index_Size col{ this->point_x }; col < point_x_; ++col)
						this->substitutionSTL(matrix_, value_pairs, col, row, args_...);
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (this->replace_num >= value_pairs.size()) {
					for (const auto& i : value_pairs)
						matrix_[i.first][i.second] = this->after_value;
					return true;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first][value_pairs[index].second] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}
				return true;
			}

			//LayerNormal
			template<typename Matrix_, typename ...Args_>
			bool drawLayerNormal(Matrix_ && matrix_, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
				if (this->replace_num == 0) return true;
				if (this->before_value.size() == 0) return false;

				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (Index_Size row{ this->point_y }; row < point_y_; ++row)
					for (Index_Size col{ this->point_x }; col < point_x_; ++col)
						this->substitutionLayer(matrix_, value_pairs, layer_, col, row, args_...);
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (this->replace_num >= value_pairs.size()) {
					for (const auto& i : value_pairs)
						matrix_[i.first][i.second][layer_] = this->after_value;
					return true;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first][value_pairs[index].second][layer_] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}
				return true;
			}

			//Array
			template<typename Matrix_, typename ...Args_>
			bool drawArray(Matrix_ && matrix_, const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_, Args_ && ... args_) const noexcept {
				if (this->replace_num == 0) return true;
				if (this->before_value.size() == 0) return false;

				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (Index_Size row{ this->point_y }; row < point_y_; ++row)
					for (Index_Size col{ this->point_x }; col < point_x_; ++col)
						this->substitutionArray(matrix_, value_pairs, col, row, max_x_, args_...);
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (this->replace_num >= value_pairs.size()) {
					for (const auto& i : value_pairs)
						matrix_[i.first * max_x_ + i.second] = this->after_value;
					return true;
				}

				for (std::size_t modify_count{}, index{}; modify_count < this->replace_num; ++modify_count) {
					index = dtl::random::mt32bit.get<std::size_t>(value_pairs.size());
					matrix_[value_pairs[index].first * max_x_ + value_pairs[index].second] = this->after_value;
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());
					if (value_pairs.size() == 0) break;
				}
				return true;
			}

		public:


			///// 情報取得 /////

#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
			[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
			[[nodiscard]]
#endif
#endif
			constexpr Index_Size getPointX() const noexcept {
				return this->point_x;
			}
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
			[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
			[[nodiscard]]
#endif
#endif
			constexpr Index_Size getPointY() const noexcept {
				return this->point_y;
			}
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
			[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
			[[nodiscard]]
#endif
#endif
			constexpr Index_Size getWidth() const noexcept {
				return this->width;
			}
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
			[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
			[[nodiscard]]
#endif
#endif
			constexpr Index_Size getHeight() const noexcept {
				return this->height;
			}
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
			[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
			[[nodiscard]]
#endif
#endif
			constexpr Matrix_Int_ getValue() const noexcept {
				return this->after_value;
			}


			///// 生成呼び出し /////

			//STL
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_) const noexcept {
				return (this->width == 0) ? this->drawSTL(std::forward<Matrix_>(matrix_), (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height) : this->drawWidthSTL(matrix_, this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawSTL(std::forward<Matrix_>(matrix_), (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height, function_) : this->drawWidthSTL(matrix_, this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height, function_);
			}

			//LayerSTL
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(std::forward<Matrix_>(matrix_), layer_, (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height) : this->drawLayerWidthSTL(matrix_, layer_, this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(std::forward<Matrix_>(matrix_), layer_, (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height, function_) : this->drawLayerWidthSTL(matrix_, layer_, this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= matrix_.size()) ? matrix_.size() : this->point_y + this->height, function_);
			}

			//Normal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawNormal(std::forward<Matrix_>(matrix_), (this->width == 0 || this->point_x + this->width >= max_x_) ? max_x_ : this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= max_y_) ? max_y_ : this->point_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawNormal(std::forward<Matrix_>(matrix_), (this->width == 0 || this->point_x + this->width >= max_x_) ? max_x_ : this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= max_y_) ? max_y_ : this->point_y + this->height, function_);
			}

			//LayerNormal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawLayerNormal(std::forward<Matrix_>(matrix_), layer_, (this->width == 0 || this->point_x + this->width >= max_x_) ? max_x_ : this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= max_y_) ? max_y_ : this->point_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawLayerNormal(std::forward<Matrix_>(matrix_), layer_, (this->width == 0 || this->point_x + this->width >= max_x_) ? max_x_ : this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= max_y_) ? max_y_ : this->point_y + this->height, function_);
			}

			//Array
			template<typename Matrix_>
			constexpr bool drawArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawArray(std::forward<Matrix_>(matrix_), (this->width == 0 || this->point_x + this->width >= max_x_) ? max_x_ : this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= max_y_) ? max_y_ : this->point_y + this->height, max_x_);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperatorArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawArray(std::forward<Matrix_>(matrix_), (this->width == 0 || this->point_x + this->width >= max_x_) ? max_x_ : this->point_x + this->width, (this->height == 0 || this->point_y + this->height >= max_y_) ? max_y_ : this->point_y + this->height, max_x_, function_);
			}


			///// 生成呼び出しファンクタ /////

			template<typename Matrix_, typename ...Args_>
			constexpr bool operator()(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				return this->draw(std::forward<Matrix_>(matrix_), std::forward<Args_>(args_)...);
			}


			///// ダンジョン行列生成 /////

			template<typename Matrix_, typename ...Args_>
			constexpr Matrix_&& create(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->draw(matrix_, std::forward<Args_>(args_)...);
				return std::forward<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			constexpr Matrix_&& createArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawArray(matrix_, std::forward<Args_>(args_)...);
				return std::forward<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			constexpr Matrix_&& createOperator(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawOperator(matrix_, std::forward<Args_>(args_)...);
				return std::forward<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			constexpr Matrix_&& createOperatorArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawOperatorArray(matrix_, std::forward<Args_>(args_)...);
				return std::forward<Matrix_>(matrix_);
			}


			///// 消去 /////

			//始点座標Xを初期値に戻す
			constexpr ReplaceSome& clearPointX() noexcept {
				this->point_x = 0;
				return *this;
			}
			//始点座標Yを初期値に戻す
			constexpr ReplaceSome& clearPointY() noexcept {
				this->point_y = 0;
				return *this;
			}
			//範囲の大きさ(X軸方向)を初期値に戻す
			constexpr ReplaceSome& clearWidth() noexcept {
				this->width = 0;
				return *this;
			}
			//範囲の大きさ(Y軸方向)を初期値に戻す
			constexpr ReplaceSome& clearHeight() noexcept {
				this->height = 0;
				return *this;
			}
			//始点座標(X,Y)を初期値に戻す
			constexpr ReplaceSome& clearPoint() noexcept {
				this->clearPointX();
				this->clearPointY();
				return *this;
			}
			//描画範囲を初期値に戻す
			constexpr ReplaceSome& clearRange() noexcept {
				this->clearPointX();
				this->clearPointY();
				this->clearWidth();
				this->clearHeight();
				return *this;
			}
			//全ての値を初期値に戻す
			constexpr ReplaceSome& clear() noexcept {
				this->clearRange();
				return *this;
			}


			///// 代入 /////

			constexpr ReplaceSome& setPointX(const Index_Size point_x_) noexcept {
				this->point_x = point_x_;
				return *this;
			}
			constexpr ReplaceSome& setPointY(const Index_Size point_y_) noexcept {
				this->point_y = point_y_;
				return *this;
			}
			constexpr ReplaceSome& setWidth(const Index_Size width_) noexcept {
				this->width = width_;
				return *this;
			}
			constexpr ReplaceSome& setHeight(const Index_Size height_) noexcept {
				this->height = height_;
				return *this;
			}
			constexpr ReplaceSome& setPoint(const Index_Size point_) noexcept {
				this->point_x = point_;
				this->point_y = point_;
				return *this;
			}
			constexpr ReplaceSome& setPoint(const Index_Size point_x_, const Index_Size point_y_) noexcept {
				this->point_x = point_x_;
				this->point_y = point_y_;
				return *this;
			}
			constexpr ReplaceSome& setRange(const Index_Size point_x_, const Index_Size point_y_, const Index_Size length_) noexcept {
				this->point_x = point_x_;
				this->point_y = point_y_;
				this->width = length_;
				this->height = length_;
				return *this;
			}
			constexpr ReplaceSome& setRange(const Index_Size point_x_, const Index_Size point_y_, const Index_Size width_, const Index_Size height_) noexcept {
				this->point_x = point_x_;
				this->point_y = point_y_;
				this->width = width_;
				this->height = height_;
				return *this;
			}
			constexpr ReplaceSome& setRange(const dtl::base::MatrixRange& matrix_range_) noexcept {
				this->point_x = matrix_range_.x;
				this->point_y = matrix_range_.y;
				this->width = matrix_range_.w;
				this->height = matrix_range_.h;
				return *this;
			}


			///// コンストラクタ /////

			constexpr ReplaceSome() noexcept = default;
			constexpr explicit ReplaceSome(const std::size_t replace_num_) noexcept
				:replace_num(replace_num_) {}
			constexpr explicit ReplaceSome(const std::size_t replace_num_, const Matrix_Int_& after_value) noexcept
				:after_value(after_value), replace_num(replace_num_) {}
			template<typename ...Args_>
			explicit ReplaceSome(const std::size_t replace_num_, const Matrix_Int_ & after_value, const Matrix_Int_ & first_before_value_, const Args_ & ... second_and_subsequent_before_value_) noexcept
				:after_value(after_value), replace_num(replace_num_) {
				this->string_String(first_before_value_, second_and_subsequent_before_value_...);
				std::sort(before_value.begin(), before_value.end());
			}
			constexpr explicit ReplaceSome(const dtl::base::MatrixRange & matrix_range_) noexcept
				:point_x(matrix_range_.x), point_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h) {}
			constexpr explicit ReplaceSome(const dtl::base::MatrixRange& matrix_range_, const std::size_t replace_num_) noexcept
				:point_x(matrix_range_.x), point_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h),
				replace_num(replace_num_) {}
			constexpr explicit ReplaceSome(const dtl::base::MatrixRange & matrix_range_, const std::size_t replace_num_, const Matrix_Int_ & after_value) noexcept
				:point_x(matrix_range_.x), point_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h),
				after_value(after_value), replace_num(replace_num_) {}
			template<typename ...Args_>
			explicit ReplaceSome(const dtl::base::MatrixRange & matrix_range_, const std::size_t replace_num_, const Matrix_Int_ & after_value, const Matrix_Int_ & first_before_value_, const Args_ & ... second_and_subsequent_before_value_) noexcept
				:point_x(matrix_range_.x), point_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h),
				after_value(after_value), replace_num(replace_num_) {
				this->string_String(first_before_value_, second_and_subsequent_before_value_...);
				std::sort(before_value.begin(), before_value.end());
			}

		};
	}
}

#include <cstddef>
#include <vector>
#include <utility>
#include <algorithm>
#include <Utility/Copy.hpp>

//STLデータ
namespace dtl {
	inline namespace utility {
		namespace stl {

			template<typename After_Int_, typename Matrix_Int_, typename Matrix_>
			bool setItem(Matrix_& matrix_, const std::size_t n_, const After_Int_ set_value_, const Matrix_Int_ clear_value_) noexcept {
				if (n_ == 0) return true;
				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (std::size_t row{}; row < matrix_.size(); ++row)
					for (std::size_t col{}; col < matrix_[row].size(); ++col)
						if (matrix_[row][col] == clear_value_) value_pairs.emplace_back(std::make_pair(row, col));
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (n_ >= value_pairs.size()) {
					for (auto&& i : value_pairs)
						dtl::utility::tool::castCopyValue(matrix_[i.first][i.second], set_value_);
					return true;
				}

				std::size_t index{ static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size()))) };
				for (std::size_t modify_count{}; modify_count < n_; ++modify_count) {

					const auto& [modify_y, modify_x] {value_pairs[index]};
					if (matrix_[modify_y][modify_x] != clear_value_) return false;

					dtl::utility::tool::castCopyValue(matrix_[modify_y][modify_x], set_value_);
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());

					if (value_pairs.size() == 0) break;
					index = static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size())));
				}
				return true;
			}
			template<typename After_Int_, typename Matrix_>
			inline bool setItem(Matrix_ & matrix_, const std::size_t n_, const After_Int_ set_value_) noexcept {
				return dtl::utility::stl::setItem(matrix_, n_, set_value_, 1);
			}
			template<typename Matrix_>
			inline bool setItem(Matrix_ & matrix_, const std::size_t n_) noexcept {
				return dtl::utility::stl::setItem(matrix_, n_, 2, 1);
			}

		} //namespace
	}
}

namespace dtl {
	inline namespace utility {
		namespace normal {

			template<typename After_Int_, typename Matrix_Int_, typename Matrix_>
			bool setItem(Matrix_& matrix_, const std::size_t x_, const std::size_t y_, const std::size_t n_, const After_Int_ set_value_, const Matrix_Int_ clear_value_) noexcept {
				if (n_ == 0) return true;
				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (std::size_t row{}; row < y_; ++row)
					for (std::size_t col{}; col < x_; ++col)
						if (matrix_[row][col] == clear_value_) value_pairs.emplace_back(std::make_pair(row, col));
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (n_ >= value_pairs.size()) {
					for (auto&& i : value_pairs)
						dtl::utility::tool::castCopyValue(matrix_[i.first][i.second], set_value_);
					return true;
				}

				std::size_t index{ static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size()))) };
				for (std::size_t modify_count{}; modify_count < n_; ++modify_count) {

					const auto& [modify_y, modify_x] {value_pairs[index]};
					if (matrix_[modify_y][modify_x] != clear_value_) return false;

					dtl::utility::tool::castCopyValue(matrix_[modify_y][modify_x], set_value_);
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());

					if (value_pairs.size() == 0) break;
					index = static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size())));
				}
				return true;
			}
			template<typename After_Int_, typename Matrix_>
			inline bool setItem(Matrix_ & matrix_, const std::size_t x_, const std::size_t y_, const std::size_t n_, const After_Int_ set_value_) noexcept {
				return dtl::utility::normal::setItem(matrix_, x_, y_, n_, set_value_, 1);
			}
			template<typename Matrix_>
			inline bool setItem(Matrix_ & matrix_, const std::size_t x_, const std::size_t y_, const std::size_t n_) noexcept {
				return dtl::utility::normal::setItem(matrix_, x_, y_, n_, 2, 1);
			}

		} //namespace
	}
}

namespace dtl {
	inline namespace utility {
		namespace array {

			template<typename After_Int_, typename Matrix_Int_, typename Matrix_>
			bool setItem(Matrix_& matrix_, const std::size_t x_, const std::size_t y_, const std::size_t n_, const After_Int_ set_value_, const Matrix_Int_ clear_value_) noexcept {
				if (n_ == 0) return true;
				std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

				for (std::size_t row{}; row < y_; ++row)
					for (std::size_t col{}; col < x_; ++col)
						if (matrix_[row * x_ + col] == clear_value_) value_pairs.emplace_back(std::make_pair(row, col));
				if (value_pairs.size() == 0) return false;
				value_pairs.shrink_to_fit();

				if (n_ >= value_pairs.size()) {
					for (auto&& i : value_pairs)
						dtl::utility::tool::castCopyValue(matrix_[i.first * x_ + i.second], set_value_);
					return true;
				}

				std::size_t index{ static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size()))) };
				for (std::size_t modify_count{}; modify_count < n_; ++modify_count) {

					const auto& [modify_y, modify_x] {value_pairs[index]};
					if (matrix_[modify_y * x_ + modify_x] != clear_value_) return false;

					dtl::utility::tool::castCopyValue(matrix_[modify_y * x_ + modify_x], set_value_);
					value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());

					if (value_pairs.size() == 0) break;
					index = static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size())));
				}
				return true;
			}
			template<typename After_Int_, typename Matrix_>
			inline bool setItem(Matrix_ & matrix_, const std::size_t x_, const std::size_t y_, const std::size_t n_, const After_Int_ set_value_) noexcept {
				return dtl::utility::array::setItem(matrix_, x_, y_, n_, set_value_, 1);
			}
			template<typename Matrix_>
			inline bool setItem(Matrix_ & matrix_, const std::size_t x_, const std::size_t y_, const std::size_t n_) noexcept {
				return dtl::utility::array::setItem(matrix_, x_, y_, n_, 2, 1);
			}

		} //namespace
	}
}

namespace dtl {
	inline namespace utility {
		namespace layer {
			namespace stl {

				template<typename After_Int_, typename Matrix_Int_, typename Matrix_>
				bool setItem(Matrix_& matrix_, const std::size_t layer_, const std::size_t n_, const After_Int_ set_value_, const Matrix_Int_ clear_value_) noexcept {
					if (n_ == 0) return true;
					std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

					for (std::size_t row{}; row < matrix_.size(); ++row)
						for (std::size_t col{}; col < matrix_[row].size(); ++col)
							if (matrix_[row][col][layer_] == clear_value_) value_pairs.emplace_back(std::make_pair(row, col));
					if (value_pairs.size() == 0) return false;
					value_pairs.shrink_to_fit();

					if (n_ >= value_pairs.size()) {
						for (auto&& i : value_pairs)
							dtl::utility::tool::castCopyValue(matrix_[i.first][i.second][layer_], set_value_);
						return true;
					}

					std::size_t index{ static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size()))) };
					for (std::size_t modify_count{}; modify_count < n_; ++modify_count) {

						const auto& [modify_y, modify_x] {value_pairs[index]};
						if (matrix_[modify_y][modify_x][layer_] != clear_value_) return false;

						dtl::utility::tool::castCopyValue(matrix_[modify_y][modify_x][layer_], set_value_);
						value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());

						if (value_pairs.size() == 0) break;
						index = static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size())));
					}
					return true;
				}
				template<typename After_Int_, typename Matrix_>
				inline bool setItem(Matrix_ & matrix_, const std::size_t layer_, const std::size_t n_, const After_Int_ set_value_) noexcept {
					return dtl::utility::layer::stl::setItem(matrix_, layer_, n_, set_value_, 1);
				}
				template<typename Matrix_>
				inline bool setItem(Matrix_ & matrix_, const std::size_t layer_, const std::size_t n_) noexcept {
					return dtl::utility::layer::stl::setItem(matrix_, layer_, n_, 2, 1);
				}

			} //namespace
		}
	}
}

namespace dtl {
	inline namespace utility {
		namespace layer {
			namespace normal {

				template<typename After_Int_, typename Matrix_Int_, typename Matrix_>
				bool setItem(Matrix_& matrix_, const std::size_t layer_, const std::size_t x_, const std::size_t y_, const std::size_t n_, const After_Int_ set_value_, const Matrix_Int_ clear_value_) noexcept {
					if (n_ == 0) return true;
					std::vector<std::pair<std::size_t, std::size_t>> value_pairs{};

					for (std::size_t row{}; row < y_; ++row)
						for (std::size_t col{}; col < x_; ++col)
							if (matrix_[row][col][layer_] == clear_value_) value_pairs.emplace_back(std::make_pair(row, col));
					if (value_pairs.size() == 0) return false;
					value_pairs.shrink_to_fit();

					if (n_ >= value_pairs.size()) {
						for (auto&& i : value_pairs)
							dtl::utility::tool::castCopyValue(matrix_[i.first][i.second][layer_], set_value_);
						return true;
					}

					std::size_t index{ static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size()))) };
					for (std::size_t modify_count{}; modify_count < n_; ++modify_count) {

						const auto& [modify_y, modify_x] {value_pairs[index]};
						if (matrix_[modify_y][modify_x][layer_] != clear_value_) return false;

						dtl::utility::tool::castCopyValue(matrix_[modify_y][modify_x][layer_], set_value_);
						value_pairs.erase(std::remove(value_pairs.begin(), value_pairs.end(), value_pairs[index]), value_pairs.end());

						if (value_pairs.size() == 0) break;
						index = static_cast<std::size_t>(dtl::random::mersenne_twister_32bit(static_cast<std::int_fast32_t>(value_pairs.size())));
					}
					return true;
				}
				template<typename After_Int_, typename Matrix_>
				inline bool setItem(Matrix_ & matrix_, const std::size_t layer_, const std::size_t x_, const std::size_t y_, const std::size_t n_, const After_Int_ set_value_) noexcept {
					return dtl::utility::layer::normal::setItem(matrix_, layer_, x_, y_, n_, set_value_, 1);
				}
				template<typename Matrix_>
				inline bool setItem(Matrix_ & matrix_, const std::size_t layer_, const std::size_t x_, const std::size_t y_, const std::size_t n_) noexcept {
					return dtl::utility::layer::normal::setItem(matrix_, layer_, x_, y_, n_, 2, 1);
				}

			} //namespace
		}
	}
}

#endif //Included Dungeon Template Library