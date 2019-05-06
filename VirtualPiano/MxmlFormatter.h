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
	std::string generate_part_header(Duration part_duration, part_id id) const;
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
	auto part_index = 0U;
	for (auto part_it = composition.begin(); part_it != composition.end(); ++part_it, part_index++) {
		out_file << "<part id=\""<< this->part_ids_[part_index] << "\">\n";
		for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
			out_file << "<measure>\n";
			if (measure_it == part_it->begin()) {
				out_file << generate_part_header(part_it->measure_duration(), part_index);
			}

			for (auto & music_symbol : *measure_it) {
				out_file << music_symbol->to_mxml();
			}

			out_file << "</measure>\n";
		}

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

template<unsigned NumberOfParts>
std::string MxmlFormatter<NumberOfParts>::generate_part_header(Duration part_duration, part_id id) const {
	return std::string("<attributes>\n")
		+ "\t<divisions>2</divisions>\n"
		+ "\t<time>\n"
		+ "\t\t<beats>" + std::to_string(part_duration.numerator()) + "</beats>\n"
		+ "\t\t<beat-type>" + std::to_string(part_duration.denominator()) + "</beat-type>\n"
		+ "\t</time>\n"
		+ "\t<clef>\n"
		+ "\t\t<sign>" + (id % 2?"F":"G") + "</sign>\n"
		+ "\t\t<line>" + (id % 2? "4":"2") + "</line>\n"
		+ "\t</clef>\n"
		+ "</attributes>\n";
}
