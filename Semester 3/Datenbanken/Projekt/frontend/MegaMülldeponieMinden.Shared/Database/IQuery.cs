namespace MegaMülldeponieMinden.Shared.Database;

public interface IQuery : IDisposable
{
    string CommandText { get; set; }
    IParameters Parameters { get; }
    
    IAsyncEnumerable<IResultRow> Execute();
}
