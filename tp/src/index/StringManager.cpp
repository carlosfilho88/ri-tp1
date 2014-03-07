/*#include <stdio.h>
#include <unicode/brkiter.h>
#include <stdlib.h>

void printUnicodeString(const UnicodeString &s) {
    char charBuf[1000];
    s.extract(0, s.length(), charBuf, sizeof(charBuf)-1, 0);   
    charBuf[sizeof(charBuf)-1] = 0;          
    printf("%s", charBuf);
}


void printTextRange( BreakIterator& iterator, 
                    int32_t start, int32_t end )
{
    CharacterIterator *strIter = iterator.getText().clone();
    UnicodeString  s;
    strIter->getText(s);

    printf(" %ld %ld\t", (long)start, (long)end);
    printUnicodeString(UnicodeString(s, 0, start));
    printf("|");
    printUnicodeString(UnicodeString(s, start, end-start));
    printf("|");
    printUnicodeString(UnicodeString(s, end));
    puts("");
    delete strIter;
}


//Print each element in order:
void printEachForward( BreakIterator& boundary)
{
    int32_t start = boundary.first();
    for (int32_t end = boundary.next();
         end != BreakIterator::DONE;
         start = end, end = boundary.next())
    {
        printTextRange( boundary, start, end );
    }
}

//Creating and using text boundaries 
int main( void )
{
    BreakIterator* boundary;
    UnicodeString stringToExamine("Cursos a distância de fotografia, estúdio fotográfico, serigrafia ou silk screen, representante comercial, bijuterias, operador de telemarketing, básico de informática, programador, lógica de programação, excel, digitação, almoxarife, comprador, eletricidade, telemensagens, recarga de cartuchos etc");
    printUnicodeString(stringToExamine);

    //print each sentence in forward and reverse order
    UErrorCode status = U_ZERO_ERROR;
    boundary = BreakIterator::createSentenceInstance(Locale::getUS(), status );
    if (U_FAILURE(status)) {
      printf("failed to create sentence break iterator.  status = %s", u_errorName(status));
      exit(1);
    }

    printf("\n Word Boundaries... \n");
    boundary = BreakIterator::createWordInstance(Locale::getUS(), status);
    boundary->setText(stringToExamine);
    puts("----- forward: -----------");
    printEachForward(*boundary);

    delete boundary;
    return 0;
}*/