using Oracle.ManagedDataAccess.Client;

namespace MegaMülldeponieMinden.Shared.Database;

public class OracleConnector : IConnector
{
    private readonly OracleConnection connection;
    private bool disposedValue;
    private bool open;

    public OracleConnector()
    {
        this.connection = new OracleConnection("[EXPUNGED]");
    }

    private void EnsureOpen()
    {
        if (!open)
        {
            this.connection.Open();
            this.open = true;
        }
    }

    public ICommand Command()
    {
        EnsureOpen();

        return new OracleCommand(this.connection.CreateCommand());
    }

    public IQuery Query()
    {
        EnsureOpen();
        
        return new OracleQuery(this.connection.CreateCommand());
    }

    protected virtual void Dispose(bool disposing)
    {
        if (!disposedValue)
        {
            if (disposing)
            {
                this.connection.Close();
                this.connection.Dispose();
            }

            disposedValue = true;
        }
    }

    public void Dispose()
    {
        Dispose(disposing: true);
        GC.SuppressFinalize(this);
    }
}
