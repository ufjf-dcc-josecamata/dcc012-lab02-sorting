#ifndef SORT_H__
#define SORT_H__


template <typename T>
void bubble_sort(T* array, int size, bool (*compare)(T&, T&))          
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (compare(array[j+1], array[j]))
            {
                T aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }
    }
     

}

template <typename T>
void insert_sort(T* array, int size,  bool (*compare)(T&, T&))
{
    for (int i = 1; i < size; i++)
    {
        T key = array[i];
        int j = i - 1;
        while (j >= 0 && compare(key, array[j]))
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}


template <typename T>
void selection_sort(T* array, int size, bool (*compare)(T&, T&))
{
    for (int i = 0; i < size; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (compare(array[j], array[min]))
                min = j;
        }
        T aux = array[i];
        array[i] = array[min];
        array[min] = aux;
    }
}

#endif /* SORT_H__ */
