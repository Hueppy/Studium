using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class AddressRepository : Repository<Address>
{

    public AddressRepository(IConnector connector) : base(connector)
    {
    }

    protected override string Table => "ADRESSE";
    protected override string KeyField => "ID_ADRESSE";

    protected override string Insert => @"
INSERT INTO ADRESSE 
  (STRASSENNAME_ADRESSE, HAUSNUMMER_ADRESSE, PLZ_ADRESSE, ADRESSENZUSATZ_ADRESSE, LAND_ADRESSE, ID_ADRESSE)
VALUES 
  (:Street, :StreetNumber, :ZipCode, :Addition, :Country, :Id)";

    protected override string Update => @"
UPDATE ADRESSE
SET
  STRASSENNAME_ADRESSE = :Street, 
  HAUSNUMMER_ADRESSE = :StreeNumber, 
  PLZ_ADRESSE = :ZipCode, 
  ADRESSENZUSATZ_ADRESSE = :Addition, 
  LAND_ADRESSE = :Country 
WHERE ID_ADRESSE = :Id    
";

    protected override long GetId(Address obj)
    {
        return obj.Id;
    }

    protected override void SetId(Address obj, long id)
    {
        obj.Id = id;
    }

    protected override async Task Read(Address obj, IResultRow row)
    {
        obj.Id = await row.AsInt("ID_ADRESSE") ?? -1;
        obj.Street = await row.AsString("STRASSENNAME_ADRESSE") ?? string.Empty;
        obj.StreetNumber = await row.AsInt("HAUSNUMMER_ADRESSE") ?? -1;
        obj.ZipCode = await row.AsInt("PLZ_ADRESSE") ?? -1;
        obj.Addition = await row.AsString("ADRESSENZUSATZ_ADRESSE") ?? string.Empty;
        obj.Country = await row.AsString("LAND_ADRESSE") ?? string.Empty;
    }

    protected override void Write(Address obj, IParameters parameters)
    {
        parameters.Add("Street", obj.Street);
        parameters.Add("StreetNumber", obj.StreetNumber);
        parameters.Add("ZipCode", obj.ZipCode);
        parameters.Add("Addition", obj.Addition);
        parameters.Add("Country", obj.Country);
        parameters.Add("Id", obj.Id);
    }
}
