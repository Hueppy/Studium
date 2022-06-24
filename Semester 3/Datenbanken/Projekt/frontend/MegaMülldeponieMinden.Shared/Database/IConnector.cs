namespace MegaMülldeponieMinden.Shared.Database;

public interface IConnector : IDisposable
{
    public ICommand Command();
    public IQuery Query();
}
