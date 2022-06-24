namespace MegaMülldeponieMinden.Shared.Database;

public interface IResultRow
{
    public int Count { get; }
    
    public Task<bool?> AsBoolean(string name);
    public Task<double?> AsDouble(string name);
    public Task<long?> AsInt(string name);
    public Task<string?> AsString(string name);
    public Task<DateTime?> AsDateTime(string name);
    
    public string Name(int i);
}
