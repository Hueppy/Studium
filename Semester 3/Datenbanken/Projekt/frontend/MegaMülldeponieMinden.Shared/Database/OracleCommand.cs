using MDAOracleCommand = Oracle.ManagedDataAccess.Client.OracleCommand;

namespace MegaMülldeponieMinden.Shared.Database;

public class OracleCommand : ICommand
{
    private readonly MDAOracleCommand command;

    public OracleCommand(MDAOracleCommand command)
    {
        this.command = command;
        this.Parameters = new OracleParameters(command.Parameters);
    }

    public string CommandText
    {
        get => this.command.CommandText;
        set => this.command.CommandText = value;
    }

    public IParameters Parameters { get; private set; }

    public void Dispose()
    {
        this.command.Dispose();
        this.Parameters.Dispose();
    }

    public async Task<int> Execute()
    {
        return await this.command.ExecuteNonQueryAsync();
    }
}
