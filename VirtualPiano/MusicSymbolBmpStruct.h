#ifndef _MUSICSYMBOLBMPSTRUCT_H_
#define _MUSICSYMBOLBMPSTRUCT_H_

namespace bmp_formatter {
	typedef struct MusicSymbolBmpStruct {
		unsigned char red, green, blue;
		unsigned num_of_pixels;
		
		explicit MusicSymbolBmpStruct() = default;

		explicit MusicSymbolBmpStruct(unsigned char red, unsigned char green, unsigned char blue, unsigned num_of_pixels);

	} music_symbol_bmp;

}

#endif
