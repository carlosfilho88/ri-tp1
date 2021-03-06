/**
 * Collection Writer
 * @author: anisio@dcc.ufmg.br
 */

#ifndef __COLLECTION_WRITER_H__
#define __COLLECTION_WRITER_H__

#include "envDefault.h"
#include "Document.h"
#include <stdint.h>
#include <cstdio>
#include <cstdlib>

namespace RICPNS {

	class CollectionWriter {
		public:

			CollectionWriter(const std::string & inputDirectory,
							 const std::string & inputIndexFileName,
							 const std::string & outputDirectory,
							 const std::string & outputIndexFileName,
							 const std::string & outputPrefixFileName);

			virtual ~CollectionWriter();
			
			// Writing compressed with zlib
			void dump();

		private:

			typedef unsigned char * TUCharPtr;

			void initialize();
			bool getNextDocument(Document & doc);
			int compressDocument(const Document & document, TUCharPtr & to, size_t & size);
			void appendDocument(const Document & document, TUCharPtr dPtr, const size_t & size);

			bool filter(const Document & doc);

			std::string inputDirectory_;
			std::string inputIndexFileName_;
			std::string outputDirectory_;
			std::string outputIndexFileName_;
			std::string outputPrefixFileName_;

			FILE * inputIndexFilePtr_;
			FILE * inputContentFilePtr_;
			FILE * outputIndexFilePtr_;
			FILE * outputContentFilePtr_;
			uint32_t outputContentIndex_;

			std::string inputContentFileName_;
			size_t outputCurrentOffset_;
	};
}

#endif

