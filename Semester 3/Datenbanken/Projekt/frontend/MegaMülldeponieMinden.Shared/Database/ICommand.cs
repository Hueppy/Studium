namespace MegaMülldeponieMinden.Shared.Database;

public interface ICommand : IDisposable
{
    string CommandText { get; set; }
    IParameters Parameters { get; }
    
    Task<int> Execute();
}
