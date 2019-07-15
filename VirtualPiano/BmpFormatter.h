#ifndef _BMPFORMATTER_H_
#define _BMPFORMATTER_H_

#include "VirtualPianoException.h"
#include "Formatter.h"
#include "MusicSymbolBmpStruct.h"

#include <vector>
#include <fstream>

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
	this->bitmap_size_ += this->width_ - this->bitmap_size_ % this->width_;
	this->height_ = (this->bitmap_size_ / this->width_);
	std::ofstream out_file{ out_file_path, std::ios::binary };
	this->output_header(out_file);

	typedef struct MusicPixelStruct {
		bmp_formatter::music_symbol_bmp pixel{};
		bool is_note_added = false;
	} music_pixel;

	std::vector<music_pixel> output_pixels;

	auto part_it = composition.begin();
	auto output_pixel_index = static_cast<unsigned>(-1);

	for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
		auto notes_in_chord = 1U;
		for (auto & music_symbol_ptr : *measure_it) {
			if (music_symbol_ptr->is_in_chord_with_previous() || output_pixels.size() > output_pixel_index + 1 && output_pixels[output_pixel_index].is_note_added) {
				auto new_bmp = music_symbol_ptr->to_bmp();
				new_bmp.red = new_bmp.red * notes_in_chord + output_pixels[output_pixel_index].pixel.red;
				new_bmp.red /= ++notes_in_chord;
				new_bmp.green = new_bmp.green * notes_in_chord + output_pixels[output_pixel_index].pixel.green;
				new_bmp.green /= notes_in_chord;
				new_bmp.blue = new_bmp.blue * notes_in_chord + output_pixels[output_pixel_index].pixel.blue;
				new_bmp.blue /= notes_in_chord;
				output_pixels[output_pixel_index].pixel = new_bmp;
				output_pixels[output_pixel_index].is_note_added = output_pixels[output_pixel_index].is_note_added || music_symbol_ptr->to_string()[0] != ' ';
			}
			else {
				output_pixel_index++;
				output_pixels.push_back({ music_symbol_ptr->to_bmp(), music_symbol_ptr->to_string()[0] != ' ' });
			}

		}

	}

	++part_it;
	output_pixel_index = static_cast<unsigned>(-1);

	for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
		auto notes_in_chord = 1U;
		for (auto & music_symbol_ptr : *measure_it) {
			if (music_symbol_ptr->is_in_chord_with_previous() || output_pixels[output_pixel_index + 1].is_note_added) {
				auto new_bmp = music_symbol_ptr->to_bmp();
				new_bmp.red = new_bmp.red * notes_in_chord + output_pixels[output_pixel_index + 1].pixel.red;
				new_bmp.red /= ++notes_in_chord;
				new_bmp.green = new_bmp.green * notes_in_chord + output_pixels[output_pixel_index + 1].pixel.green;
				new_bmp.green /= notes_in_chord;
				new_bmp.blue = new_bmp.blue * notes_in_chord + output_pixels[output_pixel_index + 1].pixel.blue;
				new_bmp.blue /= notes_in_chord;
				output_pixels[output_pixel_index + 1].pixel = new_bmp;
				output_pixels[output_pixel_index + 1].is_note_added = output_pixels[output_pixel_index + 1].is_note_added || music_symbol_ptr->to_string()[0] != ' ';
			}
			else {
				output_pixel_index++;
				output_pixels[output_pixel_index] = { music_symbol_ptr->to_bmp(),
					output_pixels[output_pixel_index].is_note_added || music_symbol_ptr->to_string()[0] != ' ' };
			}

		}

	}

	auto bytes_written = 0U;
	for (auto & output_pixel : output_pixels) {
		for (auto i = 0U; i < output_pixel.pixel.num_of_pixels; i++) {
			out_file.put(output_pixel.pixel.red);
			out_file.put(output_pixel.pixel.green);
			out_file.put(output_pixel.pixel.blue);
			bytes_written += 3;
			if (this->width_ - bytes_written % this->width_ < 3) {
				for (auto j = 0U; j < this->width_ - bytes_written % this->width_; j++) {
					out_file.put(0);
				}

				bytes_written += this->width_ - bytes_written % this->width_;
			}

		}

	}

	while (bytes_written++ < this->bitmap_size_) {
		out_file.put(0);
	}
	
}

template <unsigned NumberOfParts>
unsigned BmpFormatter<NumberOfParts>::calculate_bitmap_size(const Composition<NumberOfParts>& composition) {
	auto part_it = composition.begin();
	auto size = 0U;
	constexpr auto size_of_rgb_in_pixels = 3U;
	for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
		for (auto & music_symbol_ptr : *measure_it) {
			if (!music_symbol_ptr->is_in_chord_with_previous() || music_symbol_ptr->to_string()[0] == ' ') {
				if (music_symbol_ptr->duration() == MusicSymbol::one_quarter) {
					if (size % this->width_ + 2U > this->width_) {
						size += this->width_ - size % this->width_;
					}
					
					size += size_of_rgb_in_pixels;
					if (this->width_ - size % this->width_ < size_of_rgb_in_pixels) {
						size += this->width_ - size % this->width_;
					}

				}

				size += size_of_rgb_in_pixels;
				if (this->width_ - size % this->width_ < size_of_rgb_in_pixels) {
					size += this->width_ - size % this->width_;
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
	const unsigned int size_of_file = size_of_header + this->bitmap_size_;
	auto width = this->width_ / 3;
	char output[size_of_header] = {
		0x42, 0x4D,
		static_cast<char>(size_of_file & 0xFF), static_cast<char>((size_of_file & 0xFF00) >> 8), static_cast<char>((size_of_file & 0xFF0000) >> 2 * 8), static_cast<char>((size_of_file & 0xFF000000) >> 3 * 8),
		0x0, 0x0,
		0x0, 0x0,
		static_cast<char>(size_of_header & 0xFF), static_cast<char>((size_of_header & 0xFF00) >> 8),
		static_cast<char>((size_of_header & 0xFF0000) >> 2 * 8), static_cast<char>((size_of_header & 0xFF000000) >> 3 * 8),
		static_cast<char>(size_of_dib_header & 0xFF), static_cast<char>((size_of_dib_header & 0xFF00) >> 8),
		static_cast<char>((size_of_dib_header & 0xFF0000) >> 2 * 8), static_cast<char>((size_of_dib_header & 0xFF000000) >> 3 * 8),
		static_cast<char>(width & 0xFF), static_cast<char>((width & 0xFF00) >> 8),
		static_cast<char>((width & 0xFF0000) >> 2 * 8), static_cast<char>((width & 0xFF000000) >> 3 * 8),
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
