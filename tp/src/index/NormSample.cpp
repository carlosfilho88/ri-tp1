/*class NormSample {
public:
  // ICU service objects should be cached and reused, as usual.
  NormSample(UErrorCode &errorCode)
      : nfkc(*Normalizer2::getInstance(NULL, "nfkc", UNORM2_COMPOSE, errorCode),
        fcd(*Normalizer2::getInstance(NULL, "nfkc", UNORM2_FCD, errorCode) {}

  // Normalize a string.
  UnicodeString toNFKC(const UnicodeString &s, UErrorCode &errorCode) {
    return nfkc.normalize(s, errorCode);
  }

  // Ensure FCD before processing (like in sort key generation).
  // In practice, almost all strings pass the FCD test, so it might make sense to
  // test for it and only normalize when necessary, rather than always normalizing.
  void processText(const UnicodeString &s, UErrorCode &errorCode) {
    UnicodeString fcdString;
    const UnicodeString *ps;  // points to either s or fcdString
    int32_t spanQCYes=fcd.spanQuickCheckYes(s, errorCode);
    if(U_FAILURE(errorCode)) {
      return;  // report error
    }
    if(spanQCYes==s.length()) {
      ps=&s;  // s is already in FCD
    } else {
      // unnormalized suffix as a read-only alias (does not copy characters)
      UnicodeString unnormalized=s.tempSubString(spanQCYes);
      // set the fcdString to the FCD prefix as a read-only alias
      fcdString.setTo(FALSE, s.getBuffer(), spanQCYes);
      // automatic copy-on-write, and append the FCD'ed suffix
      fcd.normalizeSecondAndAppend(fcdString, unnormalized, errorCode);
      ps=&fcdString;
      if(U_FAILURE(errorCode)) {
        return;  // report error
      }
    }
    // ... now process the string *ps which is in FCD ...
  }
private:
  const Normalizer2 &nfkc;
  const Normalizer2 &fcd;
};*/