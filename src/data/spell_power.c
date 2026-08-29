#include "types.h"
#include "constants/spells.h"

const u16 g_awSpellPowerBase[SPELL_COUNT][SPELL_LEVELS] = {
    { 10, 20, 15 },  // Flipendo
    {  0,  0,  0 },  // Informus
    { 15, 25, 20 },  // Verdimillious
    { 30, 30, 40 },  // Diffindo
    { 23, 35, 45 },  // Incendio
    { 35, 45, 55 },  // WingardiumLeviosa
    {  0,  0,  0 },  // PetrificusTotalus
    { 30, 40, 45 },  // Glacius
    {  0,  0,  0 },  // Fumos
    {  0,  0,  0 },  // Spongify
};

const u16 g_awSpellPowerScale[SPELL_COUNT][SPELL_LEVELS] = {
    {  4,  8, 10 },  // Flipendo
    {  0,  0,  0 },  // Informus
    {  6, 12, 14 },  // Verdimillious
    { 18, 19, 20 },  // Diffindo
    {  8, 16, 18 },  // Incendio
    { 20, 21, 22 },  // WingardiumLeviosa
    {  0,  0,  0 },  // PetrificusTotalus
    { 18, 20, 20 },  // Glacius
    {  0,  0,  0 },  // Fumos
    {  0,  0,  0 },  // Spongify
};

const u16 g_awSpellMpCost[SPELL_COUNT][SPELL_LEVELS] = {
    {  0, 10, 20 },  // Flipendo
    {  0,  0,  0 },  // Informus
    {  3, 15, 25 },  // Verdimillious
    { 10,  0,  0 },  // Diffindo
    {  6, 20, 30 },  // Incendio
    { 20, 30, 40 },  // WingardiumLeviosa
    { 10, 15, 20 },  // PetrificusTotalus
    { 15, 25,  0 },  // Glacius
    {  8, 30,  0 },  // Fumos
    { 10,  0,  0 },  // Spongify
};
