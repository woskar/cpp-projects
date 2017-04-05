# C++ Sheet

## Vectors

Loop through vector with index-notation:
```
for(int i=0; i<strings.size(); ++i)
    cout << strings[i] << endl;

```

Loop through vector with iterator:
```
for(vector<string>::iterator iter = strings.begin(); iter!=strings.end(); ++iter)
{
    cout << *iter << endl;
}
```

Loop through 2D Vector Grid with index-notation
```
vector< vector<int> > grid(3, vector<int>(4, 0));

for(int row=0; row < grid.size(); ++row)
{
    for(int col=0; col < grid[row].size(); ++col)
    {
        cout << grid[row][col] << " " << flush;
    }
    cout << endl;
}
cout << endl;
```

Loop through 2D Vector Grid with iterators:
```
vector< vector<int> >::iterator itrow = grid.begin();
for(; itrow!=grid.end(); ++itrow)
{
    vector<int>::iterator itcol = (*itrow).begin();
    for(; itcol!=(*itrow).end(); ++itcol)
    {
        cout << *itcol << " " << flush;
    }
    cout << endl;
}
```
