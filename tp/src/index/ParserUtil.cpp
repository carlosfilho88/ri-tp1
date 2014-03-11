#include "StringUtil.h"
#include "ParserUtil.h"

ParserUtil::ParserUtil() : num_words(1) {}

void ParserUtil::read_collection() {

  CollectionReader* cr = new CollectionReader(INPUT_DIRECTORY, INDEX_FILENAME);
  Document doc;
  GumboOutput* output;
  size_t begin;
  unsigned int doc_num = 1;
  unsigned int doc_indexed = 0;
  vector<string> terms;
  vector<Triple> triples;
  unordered_map<unsigned int, vector<unsigned int>> frequences;
  char ch;
  doc.clear();

  double tstart, tstop, ttime;
  while (cr->getNextDocument(doc)) {
    tstart = (double)clock();

    content = doc.getText();
    begin = content.find('<');
    content = begin == content.npos ? "" : content.substr(begin, content.size());

    if(content.size() > 0) {
      output = gumbo_parse(content.c_str());
      content = extract_text_html((GumboNode*)output->root);
      if(content.size() > 0) {
        content = normalize_text(content);
        
        if(content.size() > 0) {
          terms = extract_terms(content);
          unsigned int word_position = 1;

          if(terms.size() > 0) {
            for(auto i = terms.begin(); i != terms.end(); ++i) {
              unsigned int& id_term = vocabulary[*i];

              if (id_term == 0) {
                vocabulary[*i] = num_words;
                triples.emplace_back(Triple(num_words, doc_num, word_position));
                frequences[num_words].push_back(word_position);
                num_words++;
              } else {
                triples.emplace_back(Triple(id_term, doc_num, word_position));
                frequences[id_term].push_back(word_position);
              }
              word_position++;
            }
            if(triples.size() > 0)
              write_run(triples, frequences);
            frequences.clear();
            triples.clear();
            terms.clear();
            doc.clear();
            doc_indexed++;
          }
        }
      }
      
      gumbo_destroy_output(&kGumboDefaultOptions, output);
    }
    
    tstop = (double)clock();
    ttime += (double)(tstop-tstart)/CLOCKS_PER_SEC;

    //if(doc_num % 1 == 0) {
      cout << doc_num << ";" << doc_indexed << ";" << vocabulary.size() << ";" << ttime << endl;
      ttime = 0;
    //}
    doc_num++;
    //cin >> ch;
  }
  cout << doc_num << ";" << doc_indexed << ";" << vocabulary.size() << endl;
}

/*void ParserUtil::extract_words(const string& str) {
  string result;
  UnicodeString text = UnicodeString::fromUTF8(StringPiece(str));
  UnicodeString word;
  UErrorCode status = U_ZERO_ERROR;
  BreakIterator* wordIterator = BreakIterator::createSentenceInstance(Locale::getUS(), status);
  wordIterator->setText(text);

  int32_t start = wordIterator->first();

  for(int32_t end = wordIterator->next(); end != BreakIterator::DONE; start = end, end = wordIterator->next()) {
    text.extractBetween(start, end, word);
    char charBuf[(end - start) + 1];
    word.extract(0, word.length(), charBuf, sizeof(charBuf)-1, 0);   
    charBuf[sizeof(charBuf)-1] = 0;          
    printf("%s\n", charBuf);
    //cout << word.toUTF8String(word) << endl;
  }
  delete wordIterator;
}
*/
string ParserUtil::normalize_text(const string& str) {
  if (str.size() > 0) {
    string result("");
    UnicodeString source = UnicodeString::fromUTF8(str);
    UErrorCode status = U_ZERO_ERROR;
    Transliterator *accentsConverter = Transliterator::createInstance("Lower; NFD; Latin-ASCII; [\u0301] remove; NFC;", UTRANS_FORWARD, status);
    accentsConverter->transliterate(source);
    source.toUTF8String(result);

    delete accentsConverter;
    return result;
  } else 
    return "";
}

string ParserUtil::extract_text_html(GumboNode* node) {
  if (node->type == GUMBO_NODE_TEXT) {
    return string(node->v.text.text);
  } else if (node->type == GUMBO_NODE_ELEMENT && 
            node->v.element.tag != GUMBO_TAG_SCRIPT && 
            node->v.element.tag != GUMBO_TAG_STYLE && 
            node->v.element.tag != GUMBO_TAG_IMG && 
            node->v.element.tag != GUMBO_TAG_TITLE) {
    string contents = "";
    GumboVector* children = &node->v.element.children;
    for (auto i = 0; i < children->length; ++i) {
      const string text = extract_text_html((GumboNode*) children->data[i]);
      if (i != 0 && !text.empty()) {
        contents.append(" ");
      }
      contents.append(text);
    }
    contents = trim(contents, "\n\r\b\t");
    contents = reduce(contents, "","\n\r\b\t");
    return reduce(contents);
  } else {
    return ""; 
  }
}

const char* ParserUtil::find_title(const GumboNode* root) {
  assert(root->type == GUMBO_NODE_ELEMENT);
  assert(root->v.element.children.length >= 2);

  const GumboVector* root_children = &root->v.element.children;
  GumboNode* head = NULL;
  for (auto i = 0; i < root_children->length; ++i) {
    GumboNode* child = (GumboNode*)root_children->data[i];
    if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD) {
      head = child;
      break;
    }
  }
  assert(head != NULL);

  GumboVector* head_children = &head->v.element.children;
  for (auto i = 0; i < head_children->length; ++i) {
    GumboNode* child = (GumboNode*)head_children->data[i];
    if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE) {
      if (child->v.element.children.length != 1) {
        return "<empty title>";
      }
      GumboNode* title_text = (GumboNode*)child->v.element.children.data[0];
      assert(title_text->type == GUMBO_NODE_TEXT);
      return title_text->v.text.text;
    }
  }
  return "<no title found>";
}

vector<string> ParserUtil::extract_terms(string& str) {
  vector<string> terms;
  char * dup = strdup(str.c_str());
  char * word;
  word = strtok(dup," ,.!?():\"'@#$&*;|\\^~}{[]<>¹²³³£¢¬+_-=/\n\r");
  //if(word != NULL)
  //  terms.push_back(word);
  while (word != NULL) {
    terms.push_back(word);
    word = strtok(NULL, " ,.!?():\"'@#$&*;|\\^~}{[]<>¹²³³£¢¬+_-=/\n\r");
  }
  free(word);
  free(dup);
  return terms;
}

void ParserUtil::write_run(vector<Triple>& triples, unordered_map<unsigned int, vector<unsigned int>>& frequences) {
  Inverted inv;
  FILE * file;
  file = fopen(FILENAME, "wb+");

  if (file != NULL) {
    for (auto i = triples.begin(); i != triples.end(); ++i) {
      inv.id_term = i->id_term;
      inv.doc_number = i->doc_number;
      inv.frequence = frequences[i->id_term].size();
      inv.occurrence = i->occurrence;
      fwrite((&inv), 1, sizeof(inv), file);
    }
    fclose(file);
  }

}