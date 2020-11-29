#include <stdio.h>

#include <glib.h>

const int BUF_SIZE = 90;

gboolean process_new_line(GHashTable* counts) {
    gchar buf[BUF_SIZE];
    char* p = fgets(buf, BUF_SIZE - 1, stdin);
    if (p == NULL)
        return FALSE;
    g_strchomp(buf);

    gchar** words = g_strsplit(buf, " ", -1);
    for (int word_ind = 0; words[word_ind] != NULL; ++word_ind) {
        gchar* cur_word = words[word_ind];
        g_strchomp(cur_word);
        if (cur_word[0] == '\0') {
            // removing empty strings
            continue;
        }
        gpointer value_pointer = g_hash_table_lookup(counts, cur_word);
        int* new_value = g_malloc(sizeof(int));
        if (value_pointer != NULL) {
            *new_value = *((int*)value_pointer) + 1;
        } else {
            *new_value = 1;
        }
        g_hash_table_replace(counts, g_strdup(cur_word), (gpointer)new_value);
    }
    g_strfreev(words);
    return TRUE;
}

gint array_comparator(gconstpointer a, gconstpointer b, gpointer word_counts) {
    //  negative value if a < b ; zero if a = b ; positive value if a > b
    int first = *(int*)g_hash_table_lookup(word_counts, *(char**)a);
    int second = *(int*)g_hash_table_lookup(word_counts, *(char**)b);
    gint res;
    if (first < second)
        res = 1;
    else if (first == second)
        res = 0;
    else
        res = -1;
    return res;
}

void hash_table_destroyer(gpointer data) {
    g_free(data);
}

int main(int argc, char** argv) {
    GHashTable* word_counts = g_hash_table_new_full(
        g_str_hash, g_str_equal, hash_table_destroyer, hash_table_destroyer);
    while (1) {
        if (!process_new_line(word_counts)) {
            break;
        }
    }
    GArray* words_array = g_array_new(TRUE, FALSE, sizeof(char*));
    GList* keys_list = g_hash_table_get_keys(word_counts);
    while (keys_list != NULL) {
        int* value = g_hash_table_lookup(word_counts, keys_list->data);
        g_array_append_val(words_array, keys_list->data);
        keys_list = keys_list->next;
    }

    g_array_sort_with_data(words_array, array_comparator, word_counts);

    g_printf("Total %d words\n", words_array->len);
    for (int i = 0; i < words_array->len; ++i) {
        char* cur_str = g_array_index(words_array, char*, i);
        int* value = g_hash_table_lookup(word_counts, cur_str);
        g_printf("%s -> %d\n", cur_str, *(int*)value);
    }

    g_list_free(keys_list);
    g_hash_table_destroy(word_counts);
    g_array_free(words_array, TRUE);
    return 0;
}