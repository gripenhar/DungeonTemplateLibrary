/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_STORAGE_FILE_TERRAIN_OBJ
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_STORAGE_FILE_TERRAIN_OBJ

/* Bug Check : already checked */
/* Android NDK Compile (Clang 5.0) : already checked */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <string>
#include <fstream>
#include <Base/Struct.hpp>
#include <Utility/IsOutputCast.hpp>

namespace dtl::storage {

	//�}�X���w�肵�����l�Ŗ��߂�
	template<typename Matrix_Int_,typename Value_Int_ = Matrix_Int_>
	class FileTerrainOBJ {
	private:


		///// �G�C���A�X /////

		using Index_Size = std::size_t;
		using PairSize = std::pair<Index_Size, Index_Size>;


		///// �����o�ϐ� /////

		Index_Size point_x{};
		Index_Size point_y{};
		Index_Size width{};
		Index_Size height{};
		std::string str{};
		Value_Int_ value_x{ 1 };
		Value_Int_ value_y{ 1 };
		Value_Int_ value_z{ 1 };


		///// �o�͏��� /////

		constexpr inline void mountain(const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_, std::ofstream& ofs_) const noexcept {
			ofs_ << "f " << (point_y_ * max_x_ + point_x_) << " " << ((point_y_ - 1) * max_x_ + point_x_) << " " << ((point_y_ - 1) * max_x_ + (point_x_ - 1)) << '\n';
			ofs_ << "f " << (point_y_ * max_x_ + (point_x_ - 1)) << " " << (point_y_ * max_x_ + point_x_) << " " << ((point_y_ - 1) * max_x_ + (point_x_ - 1)) << '\n';
		}

		template<typename Matrix_>
		constexpr inline void baseSTL(Matrix_&& matrix_, const Index_Size point_x_, const Index_Size point_y_, std::ofstream& ofs_) const noexcept {
			ofs_ << "v " << point_x_* value_x << " " << ((dtl::utility::isOutputCast<Matrix_Int_>()) ? static_cast<int>(matrix_[point_y_][point_x_]) : matrix_[point_y_][point_x_])* value_z << " " << point_y_* value_y << '\n';
		}
		template<typename Matrix_>
		constexpr inline void baseArray(Matrix_&& matrix_, const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_, std::ofstream& ofs_) const noexcept {
			ofs_ << "v " << point_x_* value_x << " " << ((dtl::utility::isOutputCast<Matrix_Int_>()) ? static_cast<int>(matrix_[point_y_ * max_x_ + point_x_]) : matrix_[point_y_ * max_x_ + point_x_])* value_z << " " << point_y_* value_y << '\n';
		}
		template<typename Matrix_>
		constexpr inline void baseLayer(Matrix_&& matrix_, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_, std::ofstream& ofs_) const noexcept {
			ofs_ << "v " << point_x_* value_x << " " << ((dtl::utility::isOutputCast<Matrix_Int_>()) ? static_cast<int>(matrix_[point_y_][point_x_][layer_]) : matrix_[point_y_][point_x_][layer_])* value_z << " " << point_y_* value_y << '\n';
		}


		///// ��{���� /////

		//STL
		template<typename Matrix_, typename ...Args_>
		constexpr bool writeSTL(Matrix_ && matrix_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
			std::ofstream ofs(str);
			if (ofs.fail()) return false;
			for (Index_Size row{ point_y }; row < point_y_; ++row)
				for (Index_Size col{ point_x }; col < matrix_[row].size(); ++col)
					this->baseSTL(matrix_, col, row, ofs, args_...);

			for (std::size_t row{ point_y + 1 }; row < point_y_; ++row)
				for (std::size_t col{ point_x + 2 }; col <= matrix_[row].size(); ++col)
					this->mountain(col, row, matrix_[row].size(), ofs);
			return true;
		}
		template<typename Matrix_, typename ...Args_>
		constexpr bool writeWidthSTL(Matrix_ && matrix_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
			std::ofstream ofs(str);
			if (ofs.fail()) return false;
			for (Index_Size row{ point_y }; row < point_y_; ++row)
				for (Index_Size col{ point_x }; col < matrix_[row].size() && col < point_x_; ++col)
					this->baseSTL(matrix_, col, row, ofs, args_...);

			for (std::size_t row{ point_y + 1 }; row < point_y_; ++row)
				for (std::size_t col{ point_x + 2 }; col < matrix_[row].size() && col < point_x_; ++col)
					this->mountain(col, row, (matrix_[row].size() < point_x_) ? matrix_[row].size() : point_x_, ofs);
			return true;
		}

		//LayerSTL
		template<typename Matrix_, typename ...Args_>
		constexpr bool writeLayerSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
			std::ofstream ofs(str);
			if (ofs.fail()) return false;
			for (Index_Size row{ point_y }; row < point_y_; ++row)
				for (Index_Size col{ point_x }; col < matrix_[row].size(); ++col)
					this->baseLayer(matrix_, layer_, col, row, ofs, args_...);

			for (std::size_t row{ point_y + 1 }; row < point_y_; ++row)
				for (std::size_t col{ point_x + 2 }; col <= matrix_[row].size(); ++col)
					this->mountain(col, row, matrix_[row].size(), ofs);
			return true;
		}
		template<typename Matrix_, typename ...Args_>
		constexpr bool writeLayerWidthSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
			std::ofstream ofs(str);
			if (ofs.fail()) return false;
			for (Index_Size row{ point_y }; row < point_y_; ++row)
				for (Index_Size col{ point_x }; col < matrix_[row].size() && col < point_x_; ++col)
					this->baseLayer(matrix_, layer_, col, row, ofs, args_...);

			for (std::size_t row{ point_y + 1 }; row < point_y_; ++row)
				for (std::size_t col{ point_x + 2 }; col < matrix_[row].size() && col < point_x_; ++col)
					this->mountain(col, row, (matrix_[row].size() < point_x_) ? matrix_[row].size() : point_x_, ofs);
			return true;
		}

		//Normal
		template<typename Matrix_, typename ...Args_>
		constexpr bool writeNormal(Matrix_ && matrix_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
			std::ofstream ofs(str);
			if (ofs.fail()) return false;
			for (Index_Size row{ point_y }; row < point_y_; ++row)
				for (Index_Size col{ point_x }; col < point_x_; ++col)
					this->baseSTL(matrix_, col, row, ofs, args_...);

			for (std::size_t row{ point_y + 1 }; row < point_y_; ++row)
				for (std::size_t col{ point_x + 2 }; col <= point_x_; ++col)
					this->mountain(col, row, point_x_, ofs);
			return true;
		}

		//LayerNormal
		template<typename Matrix_, typename ...Args_>
		constexpr bool writeLayerNormal(Matrix_ && matrix_, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_, Args_ && ... args_) const noexcept {
			std::ofstream ofs(str);
			if (ofs.fail()) return false;
			for (Index_Size row{ point_y }; row < point_y_; ++row)
				for (Index_Size col{ point_x }; col < point_x_; ++col)
					this->baseLayer(matrix_, layer_, col, row, ofs, args_...);

			for (std::size_t row{ point_y + 1 }; row < point_y_; ++row)
				for (std::size_t col{ point_x + 2 }; col <= point_x_; ++col)
					this->mountain(col, row, point_x_, ofs);
			return true;
		}

		//Array
		template<typename Matrix_, typename ...Args_>
		constexpr bool writeArray(Matrix_ && matrix_, const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_, Args_ && ... args_) const noexcept {
			std::ofstream ofs(str);
			if (ofs.fail()) return false;
			for (Index_Size row{ point_y }; row < point_y_; ++row)
				for (Index_Size col{ point_x }; col < point_x_; ++col)
					this->baseArray(matrix_, col, row, max_x_, ofs, args_...);

			for (std::size_t row{ point_y + 1 }; row < point_y_; ++row)
				for (std::size_t col{ point_x + 2 }; col <= point_x_; ++col)
					this->mountain(col, row, point_x_, ofs);
			return true;
		}

	public:


		///// ���擾 /////

		[[nodiscard]] constexpr Index_Size getPointX() const noexcept {
			return this->point_x;
		}
		[[nodiscard]] constexpr Index_Size getPointY() const noexcept {
			return this->point_y;
		}
		[[nodiscard]] constexpr Index_Size getWidth() const noexcept {
			return this->width;
		}
		[[nodiscard]] constexpr Index_Size getHeight() const noexcept {
			return this->height;
		}
		[[nodiscard]] constexpr std::string getString() const noexcept {
			return this->str;
		}


		///// �����Ăяo�� /////

		//STL
		template<typename Matrix_>
		constexpr bool write(Matrix_ && matrix_) const noexcept {
			return (width == 0) ? this->writeSTL(std::forward<Matrix_>(matrix_), (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height) : this->writeWidthSTL(matrix_, point_x + width, (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height);
		}
		template<typename Matrix_, typename Function_>
		constexpr bool writeOperator(Matrix_ && matrix_, Function_ && function_) const noexcept {
			return (width == 0) ? this->writeSTL(std::forward<Matrix_>(matrix_), (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height, function_) : this->writeWidthSTL(matrix_, point_x + width, (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height, function_);
		}

		//LayerSTL
		template<typename Matrix_>
		constexpr bool write(Matrix_ && matrix_, const Index_Size layer_) const noexcept {
			return (width == 0) ? this->writeLayerSTL(std::forward<Matrix_>(matrix_), layer_, (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height) : this->writeLayerWidthSTL(matrix_, layer_, point_x + width, (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height);
		}
		template<typename Matrix_, typename Function_>
		constexpr bool writeOperator(Matrix_ && matrix_, const Index_Size layer_, Function_ && function_) const noexcept {
			return (width == 0) ? this->writeLayerSTL(std::forward<Matrix_>(matrix_), layer_, (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height, function_) : this->writeLayerWidthSTL(matrix_, layer_, point_x + width, (height == 0 || point_y + height >= matrix_.size()) ? matrix_.size() : point_y + height, function_);
		}

		//Normal
		template<typename Matrix_>
		constexpr bool write(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
			return this->writeNormal(std::forward<Matrix_>(matrix_), (width == 0 || point_x + width >= max_x_) ? max_x_ : point_x + width, (height == 0 || point_y + height >= max_y_) ? max_y_ : point_y + height);
		}
		template<typename Matrix_, typename Function_>
		constexpr bool writeOperator(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
			return this->writeNormal(std::forward<Matrix_>(matrix_), (width == 0 || point_x + width >= max_x_) ? max_x_ : point_x + width, (height == 0 || point_y + height >= max_y_) ? max_y_ : point_y + height, function_);
		}

		//LayerNormal
		template<typename Matrix_>
		constexpr bool write(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
			return this->writeLayerNormal(std::forward<Matrix_>(matrix_), layer_, (width == 0 || point_x + width >= max_x_) ? max_x_ : point_x + width, (height == 0 || point_y + height >= max_y_) ? max_y_ : point_y + height);
		}
		template<typename Matrix_, typename Function_>
		constexpr bool writeOperator(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
			return this->writeLayerNormal(std::forward<Matrix_>(matrix_), layer_, (width == 0 || point_x + width >= max_x_) ? max_x_ : point_x + width, (height == 0 || point_y + height >= max_y_) ? max_y_ : point_y + height, function_);
		}

		//Array
		template<typename Matrix_>
		constexpr bool writeArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
			return this->writeArray(std::forward<Matrix_>(matrix_), (width == 0 || point_x + width >= max_x_) ? max_x_ : point_x + width, (height == 0 || point_y + height >= max_y_) ? max_y_ : point_y + height, max_x_);
		}
		template<typename Matrix_, typename Function_>
		constexpr bool writeOperatorArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
			return this->writeArray(std::forward<Matrix_>(matrix_), (width == 0 || point_x + width >= max_x_) ? max_x_ : point_x + width, (height == 0 || point_y + height >= max_y_) ? max_y_ : point_y + height, max_x_, function_);
		}


		///// �_���W�����s�񐶐� /////

		template<typename Matrix_, typename ...Args_>
		constexpr auto create(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
			this->write(matrix_, std::forward<Args_>(args_)...);
			return std::forward<Matrix_>(matrix_);
		}
		template<typename Matrix_, typename ...Args_>
		constexpr auto createArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
			this->writeArray(matrix_, std::forward<Args_>(args_)...);
			return std::forward<Matrix_>(matrix_);
		}
		template<typename Matrix_, typename ...Args_>
		constexpr auto createOperator(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
			this->writeOperator(matrix_, std::forward<Args_>(args_)...);
			return std::forward<Matrix_>(matrix_);
		}
		template<typename Matrix_, typename ...Args_>
		constexpr auto createOperatorArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
			this->writeOperatorArray(matrix_, std::forward<Args_>(args_)...);
			return std::forward<Matrix_>(matrix_);
		}


		///// �R���X�g���N�^ /////
		//Value_Int_
		constexpr FileTerrainOBJ() noexcept = default;
		constexpr explicit FileTerrainOBJ(const std::string& write_value_) noexcept
			:str(write_value_) {}
		constexpr explicit FileTerrainOBJ(const dtl::base::MatrixRange & matrix_range_) noexcept
			:point_x(matrix_range_.x), point_y(matrix_range_.y),
			width(matrix_range_.w), height(matrix_range_.h) {}
		constexpr explicit FileTerrainOBJ(const dtl::base::MatrixRange & matrix_range_, const std::string& write_value_) noexcept
			:point_x(matrix_range_.x), point_y(matrix_range_.y),
			width(matrix_range_.w), height(matrix_range_.h),
			str(write_value_) {}

		constexpr explicit FileTerrainOBJ(const std::string& write_value_, const Value_Int_& value_x_, const Value_Int_& value_y_, const Value_Int_& value_z_) noexcept
			:str(write_value_), value_x(value_x_), value_y(value_y_), value_z(value_z_) {}
		constexpr explicit FileTerrainOBJ(const dtl::base::MatrixRange& matrix_range_, const Value_Int_& value_x_, const Value_Int_& value_y_, const Value_Int_& value_z_) noexcept
			:point_x(matrix_range_.x), point_y(matrix_range_.y),
			width(matrix_range_.w), height(matrix_range_.h),
			value_x(value_x_), value_y(value_y_), value_z(value_z_) {}
		constexpr explicit FileTerrainOBJ(const dtl::base::MatrixRange& matrix_range_, const std::string& write_value_, const Value_Int_& value_x_, const Value_Int_& value_y_, const Value_Int_& value_z_) noexcept
			:point_x(matrix_range_.x), point_y(matrix_range_.y),
			width(matrix_range_.w), height(matrix_range_.h),
			str(write_value_),
			value_x(value_x_), value_y(value_y_), value_z(value_z_) {}

		constexpr explicit FileTerrainOBJ(const Index_Size point_x_, const Index_Size point_y_, const Index_Size width_, const Index_Size height_) noexcept
			:point_x(point_x_), point_y(point_y_),
			width(width_), height(height_) {}
		constexpr explicit FileTerrainOBJ(const Index_Size point_x_, const Index_Size point_y_, const Index_Size width_, const Index_Size height_, const std::string& write_value_) noexcept
			:point_x(point_x_), point_y(point_y_),
			width(width_), height(height_),
			str(write_value_) {}

		constexpr explicit FileTerrainOBJ(const Index_Size point_x_, const Index_Size point_y_, const Index_Size width_, const Index_Size height_, const Value_Int_& value_x_, const Value_Int_& value_y_, const Value_Int_& value_z_) noexcept
			:point_x(point_x_), point_y(point_y_),
			width(width_), height(height_),
			value_x(value_x_), value_y(value_y_), value_z(value_z_) {}
		constexpr explicit FileTerrainOBJ(const Index_Size point_x_, const Index_Size point_y_, const Index_Size width_, const Index_Size height_, const std::string& write_value_, const Value_Int_& value_x_, const Value_Int_& value_y_, const Value_Int_& value_z_) noexcept
			:point_x(point_x_), point_y(point_y_),
			width(width_), height(height_),
			str(write_value_),
			value_x(value_x_), value_y(value_y_), value_z(value_z_) {}
	};
}

#endif //Included Dungeon Template Library