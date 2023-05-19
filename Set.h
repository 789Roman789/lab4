struct Set;

Set set_new();
bool set_is_empty(Set const &set);
int set_example(Set const &set);
int set_constains(Set const &set, int key);
Set& set_insert(Set &set, int key);
Set& set_remove(Set &set, int key);
Set& set_erase(Set &set);