
#include "buzzer.h"
#include "platform.h"
#include "encoding.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"

#include "gpio.h"

#define CLINT_REG64(offset) (*(volatile uint64_t *) (CLINT_CTRL_ADDR + (offset)))
#define PROGRAM_SIZE 128

typedef struct instruction_t {
    uint32_t delay;
    uint32_t final_time;
    uint32_t last_time;
} instruction_t;

struct {
    instruction_t instructions[PROGRAM_SIZE];
    instruction_t *current;
    instruction_t *end;
} program;

buzzer_note_callback_t buzzer_note_callback = NULL;
const buzzer_t *current_buzzer = NULL;

void instruction_prepare(instruction_t *instruction, uint64_t time)
{
    instruction->last_time += time;
    instruction->final_time += time;
}

void buzzer_irq_tick()
{
    gpio_toggle(MASK(current_buzzer->pin_offset));

    uint64_t time = CLINT_REG64(CLINT_MTIME);
    if (time > program.current->final_time) {
        program.current++;
        if (program.current != program.end) {
            if (buzzer_note_callback != NULL) {
                buzzer_note_callback();
            }
            instruction_prepare(program.current, time);
        }
    }

    if (program.current != program.end) {
        program.current->last_time += program.current->delay;
        CLINT_REG(CLINT_MTIMECMP) = program.current->last_time;
    } else {
        clear_csr(mie, MIP_MTIP);
        current_buzzer = NULL;
    }
}

void buzzer_irq_handler() __attribute__((interrupt));

void buzzer_irq_handler()
{
    uint64_t mcause_value = read_csr(mcause);

    if ((mcause_value & 0x80000000) > 0U) {
        if ((mcause_value & 0x7FFFFFFFU) == 7U) {
            buzzer_irq_tick();
        }            
    }
}

void build_program(const song_t *song)
{    
    for (uint8_t i = 0; i < song->count; ++i) {
        int freq = song->freq[i];
        float duration = song->duration[i];

        program.instructions[i + 1U].delay      = (RTC_FREQ / (freq * 2)) * 10.9;
        program.instructions[i + 1U].last_time  = 0;
        program.instructions[i + 1U].final_time = RTC_FREQ * duration;
        
    }

    // insert dummy instruction at first position that causes
    // the first real instruction to be properly initialize
    program.instructions[0].delay      = 0;
    program.instructions[0].last_time  = 0;
    program.instructions[0].final_time = 0;
    
    program.current = &program.instructions[0];
    program.end     = &program.instructions[song->count + 2U];
}

void buzzer_init(const buzzer_t *buzzer)
{
    gpio_output(MASK(buzzer->pin_offset));
}

void buzzer_play(const buzzer_t *buzzer, const song_t *song)
{
    if (current_buzzer == NULL) {
        // if buzzer is not NULL, a song is currently playing
        
        current_buzzer = buzzer;
        // convert song to program
        build_program(song);

        // disable interrupt
        clear_csr(mstatus, MSTATUS_MIE);
        
        // initialize irq
        buzzer_irq_tick();
        
        // enable
        set_csr(mie, MIP_MTIP);

        // set handler
        write_csr(mtvec, &buzzer_irq_handler);

        // enable interrupts
        set_csr(mstatus, MSTATUS_MIE);

    }
}

