interface ISideBarState {
  entries: {
    name: string,
    isSelected: boolean,
  }[],
}

export const SIDE_BAR: ISideBarState = {
  entries: [
    {
      name: 'Редактирование профиля',
      isSelected: true,
    },
    {
      name: 'Сменить почту',
      isSelected: false,
    }
  ]
}

export const PPS_TEXT = {
  change_photo: 'Изменить фото профиля',
}
