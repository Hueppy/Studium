using System.Data;
using Oracle.ManagedDataAccess.Client;

namespace MegaMülldeponieMinden.Shared.Database;

public class OracleParameters : IParameters
{
    private readonly OracleParameterCollection collection;
    private readonly List<OracleParameter> parameters;

    public OracleParameters(OracleParameterCollection collection)
    {
        this.collection = collection;
        this.parameters = new List<OracleParameter>();
    }

    public void Add(string name, bool? value)
    {
        this.parameters.Add(this.collection.Add(name, OracleDbType.Boolean, value, ParameterDirection.Input));
    }

    public void Add(string name, double? value)
    {
        this.parameters.Add(this.collection.Add(name, OracleDbType.Double, value, ParameterDirection.Input));
    }

    public void Add(string name, long? value)
    {
        this.parameters.Add(this.collection.Add(name, OracleDbType.Long, value, ParameterDirection.Input));
    }

    public void Add(string name, string? value)
    {
        this.parameters.Add(this.collection.Add(name, OracleDbType.NChar, value, ParameterDirection.Input));
    }

    public void Add(string name, DateTime? value)
    {
        this.parameters.Add(this.collection.Add(name, OracleDbType.Date, value, ParameterDirection.Input));
    }

    public void Dispose()
    {
        foreach (var parameter in this.parameters)
        {
            parameter.Dispose();
        }
    }
}
