#ifndef _BMPFORMATTER_H_
#define _BMPFORMATTER_H_

#include "VirtualPianoException.h"
#include "Formatter.h"

template <unsigned NumberOfParts = composition::default_number_of_parts>
class BmpFormatter : public Formatter<NumberOfParts> {
public:
	BmpFormatter() = default;

	void set_bitmap_width(unsigned width_of_bmp_in_pixels);

	void generate_output_file(const std::string out_file_path, const Composition<NumberOfParts> & composition) override;
private:
	unsigned calculate_bitmap_size(const Composition<NumberOfParts> & composition);

	void output_header(std::ofstream & out_file) const;

	unsigned bitmap_size_ = 0;
	unsigned width_ = 4, height_ = 0;
};

template <unsigned NumberOfParts>
void BmpFormatter<NumberOfParts>::set_bitmap_width(unsigned width_of_bmp_in_pixels) {
	if (width_of_bmp_in_pixels % 4 != 0) {
		throw InvalidBmpWidth();
	}

	this->width_ = width_of_bmp_in_pixels;
}

template <unsigned NumberOfParts>
void BmpFormatter<NumberOfParts>::generate_output_file(const std::string out_file_path, const Composition<NumberOfParts>& composition) {
	this->bitmap_size_ = this->calculate_bitmap_size(composition);
	this->height_ = this->bitmap_size_ / this->width_; // TODO: align
	std::ofstream out_file{ out_file_path, std::ios::binary };
	this->output_header(out_file);

	// TODO: implement
	std::cout << "NOT YET IMPLEMENTED :(\n";
}

template <unsigned NumberOfParts>
unsigned BmpFormatter<NumberOfParts>::calculate_bitmap_size(const Composition<NumberOfParts>& composition) {
	auto part_it = composition.begin();
	auto size = 0U;
	constexpr auto size_of_rgb_in_pixels = 3U;
	for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
		for (auto & music_symbol_ptr : *measure_it) {
			if (music_symbol_ptr->is_in_chord_with_previous()) {
				if (music_symbol_ptr->duration() == MusicSymbol::one_quarter) {
					if (size % this->width_ + 2U > this->width_) {
						size += this->width_ - size % this->width_;
					}
					
					size += size_of_rgb_in_pixels * 2U;
				}
				else if (music_symbol_ptr->duration() == MusicSymbol::one_eight) {
					size += size_of_rgb_in_pixels * 1U;
				}

			}

		}

	}

	return size;
}

template <unsigned NumberOfParts>
void BmpFormatter<NumberOfParts>::output_header(std::ofstream & out_file) const {
	constexpr unsigned char size_of_header = 54U;
	constexpr unsigned char size_of_dib_header = 40U;
	const unsigned char size_of_file = size_of_header + this->bitmap_size_;
	char output[size_of_header] = {
		0x42, 0x4D,
		static_cast<char>(size_of_file & 0xFF), static_cast<char>((size_of_file & 0xFF00) >> 8), static_cast<char>((size_of_file & 0xFF0000) >> 2 * 8), static_cast<char>((size_of_file & 0xFF000000) >> 3 * 8),
		0x0, 0x0,
		0x0, 0x0,
		static_cast<char>(size_of_header & 0xFF), static_cast<char>((size_of_header & 0xFF00) >> 8),
		static_cast<char>((size_of_header & 0xFF0000) >> 2 * 8), static_cast<char>((size_of_header & 0xFF000000) >> 3 * 8),
		static_cast<char>(size_of_dib_header & 0xFF), static_cast<char>((size_of_dib_header & 0xFF00) >> 8),
		static_cast<char>((size_of_dib_header & 0xFF0000) >> 2 * 8), static_cast<char>((size_of_dib_header & 0xFF000000) >> 3 * 8),
		static_cast<char>(this->width_ & 0xFF), static_cast<char>((this->width_ & 0xFF00) >> 8),
		static_cast<char>((this->width_ & 0xFF0000) >> 2 * 8), static_cast<char>((this->width_ & 0xFF000000) >> 3 * 8),
		static_cast<char>(this->height_ & 0xFF), static_cast<char>((this->height_ & 0xFF00) >> 8),
		static_cast<char>((this->height_ & 0xFF0000) >> 2 * 8), static_cast<char>((this->height_ & 0xFF000000) >> 3 * 8),
		0x1, 0x0,
		0x18, 0x0,
		0x0, 0x0, 0x0, 0x0,
		static_cast<char>(this->bitmap_size_ & 0xFF), static_cast<char>((this->bitmap_size_ & 0xFF00) >> 8),
		static_cast<char>((this->bitmap_size_ & 0xFF0000) >> 2 * 8), static_cast<char>((this->bitmap_size_ & 0xFF000000) >> 3 * 8),
		0x13, 0x0B, 0x0, 0x0,
		0x13, 0x0B, 0x0, 0x0,
		0x0, 0x0, 0x0, 0x0,
		0x0, 0x0, 0x0, 0x0
	};

	out_file.write(output, size_of_header);
}

#endif
