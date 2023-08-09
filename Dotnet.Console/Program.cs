const int dimensionSize = 10000;

var timer1 = new Timer("two dimensional array");
var a2d = new int[dimensionSize][];

for (var i = 0; i < dimensionSize; i++)
    a2d[i] = new int[dimensionSize];

for (var y = 0; y < dimensionSize; y++)
{
    var a = a2d[y];
    for (var x = 0; x < dimensionSize; x++)
        a[x] = 2;
}

Console.WriteLine("two dimensional array " + dimensionSize + " x " + dimensionSize);
timer1.Stop();

var timer2 = new Timer("one dimensional array");
const int arraySize = dimensionSize * dimensionSize;
var arr = new int[arraySize];

for (var y = 0; y < dimensionSize; y++)
    for (var x = 0; x < dimensionSize; x++)
        arr[x + y * dimensionSize] = 2;

Console.WriteLine("one dimensional array " + dimensionSize + " * " + dimensionSize);
timer2.Stop();

internal class Timer
{
    private readonly string _name;
    private readonly DateTime _start;
    private DateTime _end;
    private TimeSpan _duration;

    public Timer(string name)
    {
        _name = name;
        _start = DateTime.Now;
    }

    public void Stop()
    {
        _end = DateTime.Now;
        _duration = _end - _start;
        var ms = _duration.TotalMilliseconds;
        Console.WriteLine(_name + " - timer took: " + ms + "ms");
    }
}