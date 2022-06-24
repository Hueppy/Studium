using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class ThirdPartyRepository : Repository<ThirdParty>
{
    private Repository<Address> addressRepository;
    
    public ThirdPartyRepository(
        IConnector connector,
        Repository<Address> addressRepository) : base(connector)
    {
        this.addressRepository = addressRepository;
    }

    protected override string Table => "FREMDBETRIEB";
    protected override string KeyField => "ID_FREMDBETRIEB";

    protected override string Insert => @"
INSERT INTO FREMDBETRIEB
  (NAME_FREMDBETRIEB, BESCHREIBUNG_FREMDBETRIEB, ID_ADRESSE, ID_FREMDBETRIEB)
VALUES
  (:Name, :Description, :Address, :Id)";

    protected override string Update => @"
UPDATE FREMDBETRIEB
SET
  NAME_FREMDBETRIEB = :Name,
  BESCHREIBUNG_FREMDBETRIEB = :Description,
  ID_ADRESSE = :Address
WHERE
  ID_FREMDBETRIEB = :Id";

    protected override async Task Read(ThirdParty obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_FREMDBETRIEB") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_FREMDBETRIEB") ?? string.Empty;
        
        obj.Address = await this.addressRepository.Load(await row.AsInt("ID_ADRESSE") ?? -1);
    }

    protected override long GetId(ThirdParty obj)
    {
        return obj.Id;
    }


    protected override void SetId(ThirdParty obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(ThirdParty obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Address", obj.Address.Id);
        parameters.Add("Id", obj.Id);
    }
}
