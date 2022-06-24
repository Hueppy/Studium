using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class FleetRepository : Repository<Fleet>
{
    private Repository<Address> addressRepository;
    
    public FleetRepository(
        IConnector connector,
        Repository<Address> addressRepository) : base(connector)
    {
        this.addressRepository = addressRepository;
    }

    protected override string Table => "FUHRPARK";
    protected override string KeyField => "ID_FUHRPARK";

    protected override string Insert => @"
INSERT INTO FUHRPARK
  (NAME_FUHRPARK, BESCHREIBUNG_FUHRPARK, STELLPLAETZE_FUHRPARK, ID_ADRESSE, ID_FUHRPARK)
VALUES
  (:Name, :Description, :Space, :Address, :Id)";

    protected override string Update => @"
UPDATE FUHRPARK
SET
  NAME_FUHRPARK = :Name, 
  BESCHREIBUNG_FUHRPARK = :Description, 
  STELLPLAETZE_FUHRPARK = :Space, 
  ID_ADRESSE = :Address
WHERE
  ID_FUHRPARK = :Id";

    protected override async Task Read(Fleet obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_FUHRPARK") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_FUHRPARK") ?? string.Empty;
        obj.Spaces = await row.AsInt("STELLPLAETZE_FUHRPARK") ?? 0;
        
        obj.Address = await this.addressRepository.Load(await row.AsInt("ID_ADRESSE") ?? -1);
    }

    protected override long GetId(Fleet obj)
    {
        return obj.Id;
    }


    protected override void SetId(Fleet obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(Fleet obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Space", obj.Spaces);
        parameters.Add("Address", obj.Address.Id);
        parameters.Add("Id", obj.Id);
    }
}
