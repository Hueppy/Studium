let projects = []
let sorter = new ProjectSorter()

function updateProjects() {
    const table = document.getElementById('overviewtable')
    for (const project of projects.slice(-3)) {
        table.innerHTML += `
        <tr>
          <td>${project.title}</td>
          <td>${project.date}</td>
          <td>
            <a href="project.html?id=${project.id}">${translator.translate('PROJECT_PAGE_GOTO')}</a>
          </td>
        </tr>
`
    }
}

window.addEventListener('load', async function () {
    const api = new ProjectApi()
    projects = await api.all()
    console.log(projects)

    sorter.sortProjects(projects)

    updateProjects()
})