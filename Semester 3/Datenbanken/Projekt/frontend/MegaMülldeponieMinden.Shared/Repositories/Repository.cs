using MegaMülldeponieMinden.Shared.Database;

namespace MegaMülldeponieMinden.Shared.Repositories;

public abstract class Repository<T> : IDisposable
    where T: new()
{
    private readonly Dictionary<long, T> objects;
    protected readonly IConnector connector;

    public Repository(IConnector connector)
    {
        this.connector = connector;
        this.objects = new Dictionary<long, T>();
    }

    private async Task<T> Read(IResultRow row)
    {
        var key = await row.AsInt(this.KeyField) ?? -1;
        if (!this.objects.TryGetValue(key, out var obj)) 
        {
            obj = new T();
            this.objects.Add(key, obj);
            await Read(obj, row);
        }
        else 
        {
            await Read(obj, row);
        }
        return obj;
    }

    protected abstract string Table { get; }
    protected abstract string KeyField { get; }

    protected abstract string Insert { get; }
    protected abstract string Update { get; }

    protected abstract long GetId(T obj);
    protected abstract void SetId(T obj, long id);
    protected abstract Task Read(T obj, IResultRow row);
    protected abstract void Write(T obj, IParameters parameters);

    public async Task Refresh()
    {
        using var query = this.connector.Query();
        query.CommandText = $"SELECT * FROM {this.Table}";

        await foreach (var row in query.Execute())
        {
            await Read(row);
        }
    }
    
    public virtual async Task<IEnumerable<T>> Load()
    {
        if (!this.objects.Any())
        {
            await Refresh();
        }

        return this.objects.Values;
    }
    
    public virtual async Task<T> Load(long id)
    {
        if (!this.objects.Any())
        {
            await Refresh();
        }

        if (!this.objects.ContainsKey(id)) 
        {
            return default(T);
        }
        
        return this.objects[id];
    }

    public virtual async Task Save(IEnumerable<T> collection) 
    {
        foreach (var item in collection)
        {
            await Save(item);
        }
    }
    
    public virtual async Task Save(T obj) 
    {
        if (GetId(obj) < 0)
        {
            SetId(obj, await NextId());
        }

        using var command = this.connector.Command();
        command.CommandText = this.Update;

        Write(obj, command.Parameters);

        if (await command.Execute() <= 0)
        {
            command.CommandText = this.Insert;
            await command.Execute();
        }
    }
    
    public virtual async Task Delete(long id)
    {
        using var command = this.connector.Command();
        command.CommandText = $"DELETE FROM {this.Table} WHERE {this.KeyField} = :Id";
        command.Parameters.Add("Id", id);
        await command.Execute();
    }

    private async Task<long> NextId() 
    {
        using var query = this.connector.Query();
        query.CommandText = $"SELECT MAX({this.KeyField}) + 1 AS ID FROM {this.Table}";
        await foreach (var row in query.Execute())
        {
            return await row.AsInt("ID") ?? -1;
        }
        return 0;
    }

    public void Dispose()
    {
        this.connector.Dispose();
    }
}
