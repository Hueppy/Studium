using Oracle.ManagedDataAccess.Client;

namespace MegaMülldeponieMinden.Shared.Database;

using MDAOracleCommand = Oracle.ManagedDataAccess.Client.OracleCommand;

public class OracleQuery : IQuery, IAsyncEnumerable<IResultRow>
{
    private struct ResultRow : IResultRow
    {
        private readonly OracleDataReader reader;
        private readonly IDictionary<string, int> columns;

        public ResultRow(OracleDataReader reader)
        {
            this.reader = reader;
            this.columns = new Dictionary<string, int>();
        }

        public int Count => this.reader.FieldCount;

        private bool TryFind(string name, out int n)
        {
            var result = columns.TryGetValue(name, out n);
            
            if (!result) {
                // Regenerate all names
                for (int i = 0; i < this.reader.FieldCount; ++i) {
                    Name(i);
                }
                result = columns.TryGetValue(name, out n);
            }

            return result;
        }

        private int Find(string name)
        {
            if (!TryFind(name, out int n)) {
                throw new InvalidOperationException($"Column {name} does not exist");
            }
            
            return n;
        }

        public async Task<bool?> AsBoolean(string name)
        {
            var id = Find(name);
            if (await this.reader.IsDBNullAsync(id))
            {
                return null;
            }
            
            return this.reader.GetBoolean(id);
        }

        public async Task<DateTime?> AsDateTime(string name)
        {
            var id = Find(name);
            if (await this.reader.IsDBNullAsync(id))
            {
                return null;
            }
            
            return this.reader.GetDateTime(id);
        }

        public async Task<double?> AsDouble(string name)
        {
            var id = Find(name);
            if (await this.reader.IsDBNullAsync(id))
            {
                return null;
            }
            
            return this.reader.GetDouble(id);
        }

        public async Task<long?> AsInt(string name)
        {
            var id = Find(name);
            if (await this.reader.IsDBNullAsync(id))
            {
                return null;
            }
            
            return this.reader.GetInt64(id);
        }

        public async Task<string?> AsString(string name)
        {
            var id = Find(name);
            if (await this.reader.IsDBNullAsync(id))
            {
                return null;
            }
            
            return this.reader.GetString(id);
        }

        public string Name(int i)
        {
            var name = this.reader.GetName(i);
            this.columns[name] = i;
            return name;
        }
    }

    private struct RowEnumerator : IAsyncEnumerator<IResultRow>
    {
        private readonly OracleDataReader reader;
        private readonly IResultRow row;

        public RowEnumerator(OracleDataReader reader)
        {
            this.reader = reader;
            this.row = new ResultRow(reader);
        }
        
        public IResultRow Current => row;

        public async ValueTask DisposeAsync()
        {
            await reader.DisposeAsync();
        }

        public async ValueTask<bool> MoveNextAsync()
        {
            return await reader.ReadAsync();
        }
    }

    private bool disposedValue;
    private MDAOracleCommand command;

    public OracleQuery(MDAOracleCommand command)
    {
        this.command = command;
        this.Parameters = new OracleParameters(command.Parameters);
    }

    public string CommandText
    {
        get => this.command.CommandText;
        set => this.command.CommandText = value;
     }

    public IParameters Parameters { get; }

    public IAsyncEnumerable<IResultRow> Execute()
    {
        return this;
    }

    public void Dispose()
    {
        this.command.Dispose();
    }

    public IAsyncEnumerator<IResultRow> GetAsyncEnumerator(CancellationToken cancellationToken = default)
    {
        return new RowEnumerator(this.command.ExecuteReader());
    }
}
