using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class RouteRepository : Repository<Route>
{
    private Repository<Depot> depotRepository;
    private Repository<Employee> employeeRepository;
    private Repository<ThirdParty> thirdPartyRepository;
    private Repository<Vehicle> vehicleRepository;
    private Repository<Address> addressRepository;
    
    public RouteRepository(
        IConnector connector,
        Repository<Depot> depotRepository,
        Repository<Employee> employeeRepository,
        Repository<ThirdParty> thirdPartyRepository,
        Repository<Vehicle> vehicleRepository,
        Repository<Address> addressRepository) : base(connector)
    {
        this.depotRepository = depotRepository;
        this.employeeRepository = employeeRepository;
        this.thirdPartyRepository = thirdPartyRepository;
        this.vehicleRepository = vehicleRepository;
        this.addressRepository = addressRepository;
    }

    protected override string Table => "ROUTE";
    protected override string KeyField => "ID_ROUTE";

    protected override string Insert => @"
INSERT INTO ROUTE
  (ID_DEPOT, ID_PERSONAL, ID_FREMDBETRIEB, ID_FAHRZEUG, BESCHREIBUNG_ROUTE, ART_ROUTE, ID_ROUTE)
VALUES
  (:Depot, :Employee, :ThirdParty, :Vehicle, :Description, :RouteKind, :Id)";

    protected override string Update => @"
UPDATE ROUTE
SET
  ID_DEPOT = :Depot,
  ID_PERSONAL = :Employee,
  ID_FREMDBETRIEB = :ThirdParty,
  ID_FAHRZEUG = :Vehicle,
  BESCHREIBUNG_ROUTE = :Description,
  ART_ROUTE = :RouteKind
WHERE
  ID_ROUTE = :Id";

    private async Task GetAddresses(long id, List<Address> addresses)
    {
        addresses.Clear();

        using var query = this.connector.Query();
        query.CommandText = @"
SELECT 
  ADRESSE.ID_ADRESSE
FROM ADRESSEROUTE
JOIN ADRESSE ON ADRESSEROUTE.ID_ADRESSE = ADRESSE.ID_ADRESSE
WHERE ADRESSEROUTE.ID_ROUTE = :Id
ORDER BY ADRESSEROUTE.NUMMER_ADRESSEROUTE";

        query.Parameters.Add("Id", id);

        await foreach (var row in query.Execute())
        {
            addresses.Add(await this.addressRepository.Load(await row.AsInt("ID_ADRESSE") ?? -1));
        }
    }

    protected override async Task Read(Route obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Description = await row.AsString("BESCHREIBUNG_ROUTE") ?? string.Empty;
        obj.RouteKind = await row.AsString("ART_ROUTE") ?? string.Empty;

        obj.Depot = await this.depotRepository.Load(await row.AsInt("ID_DEPOT") ?? -1);
        obj.Employee = await this.employeeRepository.Load(await row.AsInt("ID_PERSONAL") ?? -1);
        obj.ThirdParty = await this.thirdPartyRepository.Load(await row.AsInt("ID_FREMDBETRIEB") ?? -1);
        obj.Vehicle = await this.vehicleRepository.Load(await row.AsInt("ID_FAHRZEUG") ?? -1);

        await GetAddresses(obj.Id, obj.Addresses);
    }

    protected override long GetId(Route obj)
    {
        return obj.Id;
    }


    protected override void SetId(Route obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(Route obj, IParameters parameters)
    {
        parameters.Add("Depot", obj.Depot?.Id);
        parameters.Add("Employee", obj.Employee?.Id);
        parameters.Add("ThirdParty", obj.ThirdParty?.Id);
        parameters.Add("Vehicle", obj.Vehicle?.Id);
        parameters.Add("Description", obj.Description);
        parameters.Add("RouteKind", obj.RouteKind);
        parameters.Add("Id", obj.Id);
    }
}
