using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class SearchController : ControllerBase
{
    private PfotenFreundeContext context;

    public SearchController(PfotenFreundeContext context)
    {
        this.context = context;
    }

    /// <summary>
    /// Searches for a user
    /// </summary>
    [HttpGet("user")]
    public IEnumerable<User> SearchUser(string query)
    {
        var people = context.People.Where(x => x.Name.Contains(query) || x.Surname.Contains(query));
        var institutions = context.Institutions.Where(x => x.Name.Contains(query));
        
        return Enumerable.Union<User>(people, institutions);
    }

    /// <summary>
    /// Searches for a pet
    /// </summary>
    [HttpGet("pet")]
    public IEnumerable<Pet> SearchPet(string query)
    {
        return context.Pets.Where(x => x.Name.Contains(query));
    }
}
