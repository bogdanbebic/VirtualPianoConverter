#ifndef _MXMLFORMATTER_H_
#define _MXMLFORMATTER_H_

#include <string>
#include "Formatter.h"

template <unsigned NumberOfParts = composition::default_number_of_parts>
class MxmlFormatter : public Formatter<NumberOfParts> {
public:
	explicit MxmlFormatter(std::vector<std::string> part_ids = {"Right", "Left"});
	void generate_output_file(std::ostream & out_file, const Composition<NumberOfParts> & composition) override;
private:
	static void generate_header(std::ostream & out_mxml);
	void generate_part_list(std::ostream & out_mxml);
	std::vector<std::string> part_ids_;
};

#endif

template<unsigned NumberOfParts>
MxmlFormatter<NumberOfParts>::MxmlFormatter(std::vector<std::string> part_ids)
	: part_ids_(std::move(part_ids))
{
	// empty body
}

template<unsigned NumberOfParts>
void MxmlFormatter<NumberOfParts>::generate_output_file(std::ostream & out_file, const Composition<NumberOfParts> & composition) {
	generate_header(out_file);
	out_file << "<score-partwise version=\"3.1\">\n";
	generate_part_list(out_file);
	for (auto & part_id_str : this->part_ids_) {
		out_file << "<part id=\""<< part_id_str << "\">\n";

		// TODO: part to xml

		out_file << "</part>\n";
	}


	out_file << "</score-partwise>\n";
}

template<unsigned NumberOfParts>
void MxmlFormatter<NumberOfParts>::generate_header(std::ostream & out_mxml) {
	out_mxml << "<?xml version=\"1.0\"\n"
		<< "encoding=\"UTF-8\"\n"
		<< "standalone=\"no\"?>\n"
		<< "<!DOCTYPE score-partwise\n"
		<< "PUBLIC\n"
		<< "\t\"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"\n\n"
		<< "\t\"http://www.musicxml.org/dtds/partwise.dtd\">\n";
}

template<unsigned NumberOfParts>
void MxmlFormatter<NumberOfParts>::generate_part_list(std::ostream & out_mxml) {
	out_mxml << "<part-list>\n";
	for (auto & part_id_str : this->part_ids_) {
		out_mxml << "\t<score-part id=\"" << part_id_str << "\"></score-part>\n";
	}

	out_mxml << "</part-list>\n";
}
