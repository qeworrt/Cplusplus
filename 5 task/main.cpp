#include "log.h"

int main() {
    Log* log = Log::Instance();
    log->message(LOG_NORMAL, "program loaded");
    log->message(LOG_WARNING, "not ideal, but okay");
    log->message(LOG_ERROR, "error happens! help me!");
    log->print();
    Log* log2 = Log::Instance();
    log2->message(LOG_NORMAL, "new log prints the same");
    log2->print();
}
