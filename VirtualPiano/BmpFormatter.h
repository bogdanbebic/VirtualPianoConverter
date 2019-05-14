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
	static constexpr unsigned bmp_header_size = 54U;
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
	// TODO: align to (k * 4px) per row
	auto part_it = composition.begin();
	auto size = 0U;
	for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
		for (auto & music_symbol_ptr : *measure_it) {
			if (music_symbol_ptr->is_in_chord_with_previous()) {
				if (music_symbol_ptr->duration() == MusicSymbol::one_quarter) {
					if (size % this->width_ + 2U > this->width_) {
						size += this->width_ - size % this->width_;
					}
					
					size += 2U;
				}
				else if (music_symbol_ptr->duration() == MusicSymbol::one_eight) {
					size++;
				}

			}

		}

	}

	return size;
}

template <unsigned NumberOfParts>
void BmpFormatter<NumberOfParts>::output_header(std::ofstream & out_file) const {
	// TODO: implement
}

#endif
