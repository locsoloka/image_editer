typedef struct Filter {
    char *name;
    float strength;
    struct Filter *next;
} Filter;