#include <stdlib.h>
#include <limits.h>
#include "aho-corasick.h"
#include "../Queue/queue.h"

Trie pre_ac(char **word_list, size_t word_count);
void complete(Trie *t);

size_t aho_corasick(Trie trie, size_t word_count, char *text, size_t text_length) {
    trie = trie;
    word_count = word_count;
    text = text;
    text_length = text_length;
    return 0;
}

Trie pre_ac(char **word_list, size_t word_count){
    Trie trie = createTrie(100);
    for(size_t i = 0; i < word_count; i += 1){
        insertInTrie(trie, (unsigned char*)word_list[i]);
    }
    for(unsigned char a = 0; a < UCHAR_MAX; a += 1){
        if(!is_transition(trie, 0, (char)a)){
            create_transition(trie, 0, (char)a, 0);
        }
    }
    // complete(0);
    return trie;
}

void complete(Trie *t){
    Queue *q = create_queue();
    
}