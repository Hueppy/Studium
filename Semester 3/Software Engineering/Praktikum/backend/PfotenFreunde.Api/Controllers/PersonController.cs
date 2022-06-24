using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class PersonController : ControllerBase
{
	private PfotenFreundeContext context;

	public PersonController(PfotenFreundeContext context)
	{
		this.context = context;
	}

    /// <summary>
    /// Gets all people
    /// </summary>
	[HttpGet]
	public IEnumerable<Person> GetAll()
	{
		return context.People;
	}
	
    /// <summary>
    /// Gets information about the specified person
    /// </summary>
    /// <response code="404">Person not found</response>
    [HttpGet("{id}")]
    public async Task<ActionResult<Person>> Get(int id)
    {
		var person = await this.context.People.FindAsync(id);

		if (person == null)
		{
			return NotFound();
		}

		return person;
    }

    /// <summary>
    /// Adds a new person
    /// </summary>
    [HttpPost]
    public async Task Post(Person person)
    {
        await this.context.AddAsync(person);
		await this.context.SaveChangesAsync();
    }

    /// <summary>
    /// Updates information of the specified person
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">Person not found</response>
    [HttpPatch("{id}")]
    public async Task<ActionResult> Patch(int id, Person person)
    {
		person.Id = id;
		this.context.People.Update(person);

		await this.context.SaveChangesAsync();

		return Ok();
    }

    /// <summary>
    /// Gets the list of pets of the specified person
    /// </summary>
    [HttpGet("{id}/Pets")]
    public IEnumerable<Pet> GetPets(int id)
    {
        return this.context.Pets.Where(x => x.OwnerId == id);
    }
}
