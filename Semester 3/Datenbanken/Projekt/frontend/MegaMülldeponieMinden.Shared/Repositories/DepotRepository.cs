using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class DepotRepository : Repository<Depot>
{
    private Repository<Address> addressRepository;
    
    public DepotRepository(
        IConnector connector,
        Repository<Address> addressRepository) : base(connector)
    {
        this.addressRepository = addressRepository;
    }

    protected override string Table => "DEPOT";
    protected override string KeyField => "ID_DEPOT";

    protected override string Insert => @"
INSERT INTO DEPOT
(ID_ADRESSE, NAME_DEPOT, GROESSE_DEPOT, LAGERKAPAZITAT_DEPOT, ID_DEPOT)
VALUES
(:Address, :Name, :Size, :Capacity, :Id)";

    protected override string Update => @"
UPDATE DEPOT
SET
  ID_ADRESSE = :Address,
  NAME_DEPOT = :Name,
  GROESSE_DEPOT = :Size,
  LAGERKAPAZITAT_DEPOT = :Capacity
WHERE
  ID_DEPOT = :Id
";

    protected override long GetId(Depot obj)
    {
        return obj.Id;
    }

    protected override async Task Read(Depot obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_DEPOT") ?? string.Empty;
        obj.Size = await row.AsDouble("GROESSE_DEPOT") ?? -1;
        obj.Capacity = await row.AsInt("LAGERKAPAZITAT_DEPOT") ?? -1;
        
        obj.Address = await this.addressRepository.Load(await row.AsInt("ID_ADRESSE") ?? -1);
    }

    protected override void SetId(Depot obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(Depot obj, IParameters parameters)
    {
        parameters.Add("Address", obj.Address.Id);
        parameters.Add("Name", obj.Name);
        parameters.Add("Size", obj.Size);
        parameters.Add("Capacity", obj.Capacity);
        parameters.Add("Id", obj.Id);
    }
}
