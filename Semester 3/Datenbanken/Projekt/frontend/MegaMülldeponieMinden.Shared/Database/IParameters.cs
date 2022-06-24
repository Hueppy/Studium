namespace MegaMülldeponieMinden.Shared.Database;

public interface IParameters : IDisposable
{
    public void Add(string name, bool? value);
    public void Add(string name, double? value);
    public void Add(string name, long? value);
    public void Add(string name, string? value);
    public void Add(string name, DateTime? value );
}
